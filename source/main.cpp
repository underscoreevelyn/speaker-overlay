#define TESLA_INIT_IMPL
#include <tesla.hpp>

class GuiTest : public tsl::Gui {
public:
  GuiTest() {}

  // Called when this Gui gets loaded to create the UI
  virtual tsl::elm::Element *createUI() override {
    auto frame = new tsl::elm::OverlayFrame("speaker-overlay", "v0.0.1");

    auto list = new tsl::elm::List();

    auto not_selected = "";
    auto selected = "🗸";

    AudioTarget current_target;
    audctlGetDefaultTarget(&current_target);

    auto speaker_button = new tsl::elm::ListItem(
        "Speakers",
        (current_target == AudioTarget_Speaker) ? selected : not_selected);
    speaker_button->setClickListener([](u64 keys) {
      if (keys & HidNpadButton_A) {
        audctlSetDefaultTarget(AudioTarget_Speaker, 0, 0);
        return true;
      }

      return false;
    });

    auto headphone_button = new tsl::elm::ListItem(
        "Headphones",
        (current_target == AudioTarget_Headphone) ? selected : not_selected);
    headphone_button->setClickListener([](u64 keys) {
      if (keys & HidNpadButton_A) {
        audctlSetDefaultTarget(AudioTarget_Headphone, 0, 0);
        return true;
      }

      return false;
    });

    auto tv_button = new tsl::elm::ListItem(
        "Tv", (current_target == AudioTarget_Tv) ? selected : not_selected);
    tv_button->setClickListener([](u64 keys) {
      if (keys & HidNpadButton_A) {
        audctlSetDefaultTarget(AudioTarget_Tv, 0, 0);
        return true;
      }

      return false;
    });

    auto usb_button = new tsl::elm::ListItem(
        "USB", (current_target == AudioTarget_UsbOutputDevice) ? selected
                                                               : not_selected);
    usb_button->setClickListener([](u64 keys) {
      if (keys & HidNpadButton_A) {
        audctlSetDefaultTarget(AudioTarget_UsbOutputDevice, 0, 0);
        return true;
      }

      return false;
    });

    auto bluetooth_button = new tsl::elm::ListItem(
        "Bluetooth",
        (current_target == AudioTarget_Bluetooth) ? selected : not_selected);
    bluetooth_button->setClickListener([](u64 keys) {
      if (keys & HidNpadButton_A) {
        audctlSetDefaultTarget(AudioTarget_Bluetooth, 0, 0);
        return true;
      }

      return false;
    });

    list->addItem(speaker_button);
    list->addItem(headphone_button);
    list->addItem(tv_button);
    list->addItem(usb_button);
    list->addItem(bluetooth_button);

    frame->setContent(list);

    return frame;
  }

  // Called once every frame to update values
  virtual void update() override {}

  // Called once every frame to handle inputs not handled by other UI elements
  virtual bool handleInput(u64 keysDown, u64 keysHeld,
                           const HidTouchState &touchPos,
                           HidAnalogStickState joyStickPosLeft,
                           HidAnalogStickState joyStickPosRight) override {
    return false; // Return true here to signal the inputs have been consumed
  }
};

class OverlayTest : public tsl::Overlay {
public:
  virtual void initServices() override { audctlInitialize(); }

  virtual void exitServices() override { audctlExit(); }

  virtual std::unique_ptr<tsl::Gui> loadInitialGui() override {
    return initially<GuiTest>(); // Initial Gui to load. It's possible to pass
                                 // arguments to it's constructor like this
  }
};

int main(int argc, char **argv) { return tsl::loop<OverlayTest>(argc, argv); }
