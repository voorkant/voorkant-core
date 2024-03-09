

#pragma once

#include <optional>

#include <nlohmann/json.hpp>

#include "../HAEntity.hpp"

using json = nlohmann::json;
using std::optional;

#if 0
enum class EntityType
{
  Alarm_control_panel,
  Automation,
  Backup,
  Button,
  Calendar,
  Camera,
  Climate,
  Cloud,
  Conversation,
  Counter,
  Cover,
  Date,
  Datetime,
  Demo,
  Device_tracker,
  Fan,
  Ffmpeg,
  Frontend,
  Group,
  Homeassistant,
  Humidifier,
  Image_processing,
  Input_boolean,
  Input_button,
  Input_datetime,
  Input_number,
  Input_select,
  Input_text,
  Light,
  Lock,
  Logbook,
  Logger,
  Media_player,
  Notify,
  Number,
  Persistent_notification,
  Person,
  Recorder,
  Scene,
  Schedule,
  Script,
  Select,
  Shopping_list,
  Siren,
  Switch,
  System_log,
  Text,
  Time,
  Timer,
  Todo,
  Tts,
  Update,
  Vacuum,
  Water_heater,
  Weather,
  Zone,
  OTHER,
};
#endif

namespace HADomains
{

// START HEADER FOR AlarmControlPanel

class AlarmControlPanel
{
public:
  AlarmControlPanel(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Alarm_control_panel;
  // Arm away
  // Sets the alarm to: _armed, no one home_.
  struct AlarmArmAwayArgs
  {
    optional<json> code;
  };
  void alarmArmAway([[maybe_unused]] const AlarmArmAwayArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_arm_away";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.code) {
      cmd["service_data"]["code"] = *_args.code;
    }

    entity->wsConnSend(cmd);
  }

  // Arm with custom bypass
  // Arms the alarm while allowing to bypass a custom area.
  struct AlarmArmCustomBypassArgs
  {
    optional<json> code;
  };
  void alarmArmCustomBypass([[maybe_unused]] const AlarmArmCustomBypassArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_arm_custom_bypass";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.code) {
      cmd["service_data"]["code"] = *_args.code;
    }

    entity->wsConnSend(cmd);
  }

  // Arm home
  // Sets the alarm to: _armed, but someone is home_.
  struct AlarmArmHomeArgs
  {
    optional<json> code;
  };
  void alarmArmHome([[maybe_unused]] const AlarmArmHomeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_arm_home";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.code) {
      cmd["service_data"]["code"] = *_args.code;
    }

    entity->wsConnSend(cmd);
  }

  // Arm night
  // Sets the alarm to: _armed for the night_.
  struct AlarmArmNightArgs
  {
    optional<json> code;
  };
  void alarmArmNight([[maybe_unused]] const AlarmArmNightArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_arm_night";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.code) {
      cmd["service_data"]["code"] = *_args.code;
    }

    entity->wsConnSend(cmd);
  }

  // Arm vacation
  // Sets the alarm to: _armed for vacation_.
  struct AlarmArmVacationArgs
  {
    optional<json> code;
  };
  void alarmArmVacation([[maybe_unused]] const AlarmArmVacationArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_arm_vacation";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.code) {
      cmd["service_data"]["code"] = *_args.code;
    }

    entity->wsConnSend(cmd);
  }

  // Disarm
  // Disarms the alarm.
  struct AlarmDisarmArgs
  {
    optional<json> code;
  };
  void alarmDisarm([[maybe_unused]] const AlarmDisarmArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_disarm";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.code) {
      cmd["service_data"]["code"] = *_args.code;
    }

    entity->wsConnSend(cmd);
  }

  // Trigger
  // Enables an external alarm trigger.
  struct AlarmTriggerArgs
  {
    optional<json> code;
  };
  void alarmTrigger([[maybe_unused]] const AlarmTriggerArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_trigger";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.code) {
      cmd["service_data"]["code"] = *_args.code;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Automation

class Automation
{
public:
  Automation(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Automation;
  // Reload
  // Reloads the automation configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "automation";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Toggle
  // Toggles (enable / disable) an automation.
  struct ToggleArgs
  {
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "automation";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Trigger
  // Triggers the actions of an automation.
  struct TriggerArgs
  {
    optional<json> skip_condition;
  };
  void trigger([[maybe_unused]] const TriggerArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "automation";
    cmd["service"] = "trigger";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.skip_condition) {
      cmd["service_data"]["skip_condition"] = *_args.skip_condition;
    }

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Disables an automation.
  struct TurnOffArgs
  {
    optional<json> stop_actions;
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "automation";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.stop_actions) {
      cmd["service_data"]["stop_actions"] = *_args.stop_actions;
    }

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Enables an automation.
  struct TurnOnArgs
  {
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "automation";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Backup

class Backup
{
public:
  Backup(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Backup;
  // Create backup
  // Creates a new backup.
  struct CreateArgs
  {
  };
  void create([[maybe_unused]] const CreateArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "backup";
    cmd["service"] = "create";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Button

class Button
{
public:
  Button(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Button;
  // Press
  // Press the button entity.
  struct PressArgs
  {
  };
  void press([[maybe_unused]] const PressArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "button";
    cmd["service"] = "press";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Calendar

class Calendar
{
public:
  Calendar(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Calendar;
  // Create event
  // Adds a new calendar event.
  struct CreateEventArgs
  {
    optional<json> description;
    optional<json> end_date;
    optional<json> end_date_time;
    optional<json> in;
    optional<json> location;
    optional<json> start_date;
    optional<json> start_date_time;
    optional<json> summary;
  };
  void createEvent([[maybe_unused]] const CreateEventArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "calendar";
    cmd["service"] = "create_event";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.description) {
      cmd["service_data"]["description"] = *_args.description;
    }
    if (_args.end_date) {
      cmd["service_data"]["end_date"] = *_args.end_date;
    }
    if (_args.end_date_time) {
      cmd["service_data"]["end_date_time"] = *_args.end_date_time;
    }
    if (_args.in) {
      cmd["service_data"]["in"] = *_args.in;
    }
    if (_args.location) {
      cmd["service_data"]["location"] = *_args.location;
    }
    if (_args.start_date) {
      cmd["service_data"]["start_date"] = *_args.start_date;
    }
    if (_args.start_date_time) {
      cmd["service_data"]["start_date_time"] = *_args.start_date_time;
    }
    if (_args.summary) {
      cmd["service_data"]["summary"] = *_args.summary;
    }

    entity->wsConnSend(cmd);
  }

  // Get events
  // Get events on a calendar within a time range.
  struct GetEventsArgs
  {
    optional<json> duration;
    optional<json> end_date_time;
    optional<json> start_date_time;
  };
  void getEvents([[maybe_unused]] const GetEventsArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "calendar";
    cmd["service"] = "get_events";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.duration) {
      cmd["service_data"]["duration"] = *_args.duration;
    }
    if (_args.end_date_time) {
      cmd["service_data"]["end_date_time"] = *_args.end_date_time;
    }
    if (_args.start_date_time) {
      cmd["service_data"]["start_date_time"] = *_args.start_date_time;
    }

    entity->wsConnSend(cmd);
  }

  // List event
  // Lists events on a calendar within a time range.
  struct ListEventsArgs
  {
    optional<json> duration;
    optional<json> end_date_time;
    optional<json> start_date_time;
  };
  void listEvents([[maybe_unused]] const ListEventsArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "calendar";
    cmd["service"] = "list_events";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.duration) {
      cmd["service_data"]["duration"] = *_args.duration;
    }
    if (_args.end_date_time) {
      cmd["service_data"]["end_date_time"] = *_args.end_date_time;
    }
    if (_args.start_date_time) {
      cmd["service_data"]["start_date_time"] = *_args.start_date_time;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Camera

class Camera
{
public:
  Camera(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Camera;
  // Disable motion detection
  // Disables the motion detection.
  struct DisableMotionDetectionArgs
  {
  };
  void disableMotionDetection([[maybe_unused]] const DisableMotionDetectionArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "disable_motion_detection";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Enable motion detection
  // Enables the motion detection.
  struct EnableMotionDetectionArgs
  {
  };
  void enableMotionDetection([[maybe_unused]] const EnableMotionDetectionArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "enable_motion_detection";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Play stream
  // Plays the camera stream on a supported media player.
  struct PlayStreamArgs
  {
    optional<json> format;
    optional<json> media_player;
  };
  void playStream([[maybe_unused]] const PlayStreamArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "play_stream";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.format) {
      cmd["service_data"]["format"] = *_args.format;
    }
    if (_args.media_player) {
      cmd["service_data"]["media_player"] = *_args.media_player;
    }

    entity->wsConnSend(cmd);
  }

  // Record
  // Creates a recording of a live camera feed.
  struct RecordArgs
  {
    optional<json> duration;
    optional<json> filename;
    optional<json> lookback;
  };
  void record([[maybe_unused]] const RecordArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "record";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.duration) {
      cmd["service_data"]["duration"] = *_args.duration;
    }
    if (_args.filename) {
      cmd["service_data"]["filename"] = *_args.filename;
    }
    if (_args.lookback) {
      cmd["service_data"]["lookback"] = *_args.lookback;
    }

    entity->wsConnSend(cmd);
  }

  // Take snapshot
  // Takes a snapshot from a camera.
  struct SnapshotArgs
  {
    optional<json> filename;
  };
  void snapshot([[maybe_unused]] const SnapshotArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "snapshot";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.filename) {
      cmd["service_data"]["filename"] = *_args.filename;
    }

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Turns off the camera.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Turns on the camera.
  struct TurnOnArgs
  {
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Climate

class Climate
{
public:
  Climate(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Climate;
  // Turn on/off auxiliary heater
  // Turns auxiliary heater on/off.
  struct SetAuxHeatArgs
  {
    optional<json> aux_heat;
  };
  void setAuxHeat([[maybe_unused]] const SetAuxHeatArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_aux_heat";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.aux_heat) {
      cmd["service_data"]["aux_heat"] = *_args.aux_heat;
    }

    entity->wsConnSend(cmd);
  }

  // Set fan mode
  // Sets fan operation mode.
  struct SetFanModeArgs
  {
    optional<json> fan_mode;
  };
  void setFanMode([[maybe_unused]] const SetFanModeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_fan_mode";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.fan_mode) {
      cmd["service_data"]["fan_mode"] = *_args.fan_mode;
    }

    entity->wsConnSend(cmd);
  }

  // Set target humidity
  // Sets target humidity.
  struct SetHumidityArgs
  {
    optional<json> humidity;
  };
  void setHumidity([[maybe_unused]] const SetHumidityArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_humidity";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.humidity) {
      cmd["service_data"]["humidity"] = *_args.humidity;
    }

    entity->wsConnSend(cmd);
  }

  // Set HVAC mode
  // Sets HVAC operation mode.
  struct SetHvacModeArgs
  {
    optional<json> hvac_mode;
  };
  void setHvacMode([[maybe_unused]] const SetHvacModeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_hvac_mode";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.hvac_mode) {
      cmd["service_data"]["hvac_mode"] = *_args.hvac_mode;
    }

    entity->wsConnSend(cmd);
  }

  // Set preset mode
  // Sets preset mode.
  struct SetPresetModeArgs
  {
    optional<json> preset_mode;
  };
  void setPresetMode([[maybe_unused]] const SetPresetModeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_preset_mode";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.preset_mode) {
      cmd["service_data"]["preset_mode"] = *_args.preset_mode;
    }

    entity->wsConnSend(cmd);
  }

  // Set swing mode
  // Sets swing operation mode.
  struct SetSwingModeArgs
  {
    optional<json> swing_mode;
  };
  void setSwingMode([[maybe_unused]] const SetSwingModeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_swing_mode";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.swing_mode) {
      cmd["service_data"]["swing_mode"] = *_args.swing_mode;
    }

    entity->wsConnSend(cmd);
  }

  // Set target temperature
  // Sets target temperature.
  struct SetTemperatureArgs
  {
    optional<json> hvac_mode;
    optional<json> target_temp_high;
    optional<json> target_temp_low;
    optional<json> temperature;
  };
  void setTemperature([[maybe_unused]] const SetTemperatureArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_temperature";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.hvac_mode) {
      cmd["service_data"]["hvac_mode"] = *_args.hvac_mode;
    }
    if (_args.target_temp_high) {
      cmd["service_data"]["target_temp_high"] = *_args.target_temp_high;
    }
    if (_args.target_temp_low) {
      cmd["service_data"]["target_temp_low"] = *_args.target_temp_low;
    }
    if (_args.temperature) {
      cmd["service_data"]["temperature"] = *_args.temperature;
    }

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Turns climate device off.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Turns climate device on.
  struct TurnOnArgs
  {
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Cloud

class Cloud
{
public:
  Cloud(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Cloud;
  // Remote connect
  // Makes the instance UI accessible from outside of the local network by using Home Assistant Cloud.
  struct RemoteConnectArgs
  {
  };
  void remoteConnect([[maybe_unused]] const RemoteConnectArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cloud";
    cmd["service"] = "remote_connect";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Remote disconnect
  // Disconnects the Home Assistant UI from the Home Assistant Cloud. You will no longer be able to access your Home Assistant instance from outside your local network.
  struct RemoteDisconnectArgs
  {
  };
  void remoteDisconnect([[maybe_unused]] const RemoteDisconnectArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cloud";
    cmd["service"] = "remote_disconnect";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Conversation

class Conversation
{
public:
  Conversation(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Conversation;
  // Process
  // Launches a conversation from a transcribed text.
  struct ProcessArgs
  {
    optional<json> agent_id;
    optional<json> language;
    optional<json> text;
  };
  void process([[maybe_unused]] const ProcessArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "conversation";
    cmd["service"] = "process";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.agent_id) {
      cmd["service_data"]["agent_id"] = *_args.agent_id;
    }
    if (_args.language) {
      cmd["service_data"]["language"] = *_args.language;
    }
    if (_args.text) {
      cmd["service_data"]["text"] = *_args.text;
    }

    entity->wsConnSend(cmd);
  }

  // Reload
  // Reloads the intent configuration.
  struct ReloadArgs
  {
    optional<json> agent_id;
    optional<json> language;
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "conversation";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.agent_id) {
      cmd["service_data"]["agent_id"] = *_args.agent_id;
    }
    if (_args.language) {
      cmd["service_data"]["language"] = *_args.language;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Counter

class Counter
{
public:
  Counter(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Counter;
  // Decrement
  // Decrements a counter.
  struct DecrementArgs
  {
  };
  void decrement([[maybe_unused]] const DecrementArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "counter";
    cmd["service"] = "decrement";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Increment
  // Increments a counter.
  struct IncrementArgs
  {
  };
  void increment([[maybe_unused]] const IncrementArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "counter";
    cmd["service"] = "increment";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Reset
  // Resets a counter.
  struct ResetArgs
  {
  };
  void reset([[maybe_unused]] const ResetArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "counter";
    cmd["service"] = "reset";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Set
  // Sets the counter value.
  struct SetValueArgs
  {
    optional<json> value;
  };
  void setValue([[maybe_unused]] const SetValueArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "counter";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.value) {
      cmd["service_data"]["value"] = *_args.value;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Cover

class Cover
{
public:
  Cover(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Cover;
  // Close
  // Closes a cover.
  struct CloseCoverArgs
  {
  };
  void closeCover([[maybe_unused]] const CloseCoverArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "close_cover";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Close tilt
  // Tilts a cover to close.
  struct CloseCoverTiltArgs
  {
  };
  void closeCoverTilt([[maybe_unused]] const CloseCoverTiltArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "close_cover_tilt";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Open
  // Opens a cover.
  struct OpenCoverArgs
  {
  };
  void openCover([[maybe_unused]] const OpenCoverArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "open_cover";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Open tilt
  // Tilts a cover open.
  struct OpenCoverTiltArgs
  {
  };
  void openCoverTilt([[maybe_unused]] const OpenCoverTiltArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "open_cover_tilt";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Set position
  // Moves a cover to a specific position.
  struct SetCoverPositionArgs
  {
    optional<json> position;
  };
  void setCoverPosition([[maybe_unused]] const SetCoverPositionArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "set_cover_position";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.position) {
      cmd["service_data"]["position"] = *_args.position;
    }

    entity->wsConnSend(cmd);
  }

  // Set tilt position
  // Moves a cover tilt to a specific position.
  struct SetCoverTiltPositionArgs
  {
    optional<json> tilt_position;
  };
  void setCoverTiltPosition([[maybe_unused]] const SetCoverTiltPositionArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "set_cover_tilt_position";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.tilt_position) {
      cmd["service_data"]["tilt_position"] = *_args.tilt_position;
    }

    entity->wsConnSend(cmd);
  }

  // Stop
  // Stops the cover movement.
  struct StopCoverArgs
  {
  };
  void stopCover([[maybe_unused]] const StopCoverArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "stop_cover";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Stop tilt
  // Stops a tilting cover movement.
  struct StopCoverTiltArgs
  {
  };
  void stopCoverTilt([[maybe_unused]] const StopCoverTiltArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "stop_cover_tilt";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Toggle
  // Toggles a cover open/closed.
  struct ToggleArgs
  {
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Toggle tilt
  // Toggles a cover tilt open/closed.
  struct ToggleCoverTiltArgs
  {
  };
  void toggleCoverTilt([[maybe_unused]] const ToggleCoverTiltArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "toggle_cover_tilt";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Date

class Date
{
public:
  Date(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Date;
  // Set date
  // Sets the date.
  struct SetValueArgs
  {
    optional<json> date;
  };
  void setValue([[maybe_unused]] const SetValueArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "date";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.date) {
      cmd["service_data"]["date"] = *_args.date;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Datetime

class Datetime
{
public:
  Datetime(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Datetime;
  // Set date/time
  // Sets the date/time for a datetime entity.
  struct SetValueArgs
  {
    optional<json> datetime;
  };
  void setValue([[maybe_unused]] const SetValueArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "datetime";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.datetime) {
      cmd["service_data"]["datetime"] = *_args.datetime;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Demo

class Demo
{
public:
  Demo(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Demo;
  // Randomize device tracker data
  // Demonstrates using a device tracker to see where devices are located.
  struct RandomizeDeviceTrackerDataArgs
  {
  };
  void randomizeDeviceTrackerData([[maybe_unused]] const RandomizeDeviceTrackerDataArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "demo";
    cmd["service"] = "randomize_device_tracker_data";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR DeviceTracker

class DeviceTracker
{
public:
  DeviceTracker(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Device_tracker;
  // See
  // Records a seen tracked device.
  struct SeeArgs
  {
    optional<json> battery;
    optional<json> dev_id;
    optional<json> gps;
    optional<json> gps_accuracy;
    optional<json> host_name;
    optional<json> location_name;
    optional<json> mac;
  };
  void see([[maybe_unused]] const SeeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "device_tracker";
    cmd["service"] = "see";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.battery) {
      cmd["service_data"]["battery"] = *_args.battery;
    }
    if (_args.dev_id) {
      cmd["service_data"]["dev_id"] = *_args.dev_id;
    }
    if (_args.gps) {
      cmd["service_data"]["gps"] = *_args.gps;
    }
    if (_args.gps_accuracy) {
      cmd["service_data"]["gps_accuracy"] = *_args.gps_accuracy;
    }
    if (_args.host_name) {
      cmd["service_data"]["host_name"] = *_args.host_name;
    }
    if (_args.location_name) {
      cmd["service_data"]["location_name"] = *_args.location_name;
    }
    if (_args.mac) {
      cmd["service_data"]["mac"] = *_args.mac;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Fan

class Fan
{
public:
  Fan(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Fan;
  // Decrease speed
  // Decreases the speed of the fan.
  struct DecreaseSpeedArgs
  {
    optional<json> percentage_step;
  };
  void decreaseSpeed([[maybe_unused]] const DecreaseSpeedArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "decrease_speed";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.percentage_step) {
      cmd["service_data"]["percentage_step"] = *_args.percentage_step;
    }

    entity->wsConnSend(cmd);
  }

  // Increase speed
  // Increases the speed of the fan.
  struct IncreaseSpeedArgs
  {
    optional<json> percentage_step;
  };
  void increaseSpeed([[maybe_unused]] const IncreaseSpeedArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "increase_speed";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.percentage_step) {
      cmd["service_data"]["percentage_step"] = *_args.percentage_step;
    }

    entity->wsConnSend(cmd);
  }

  // Oscillate
  // Controls oscillatation of the fan.
  struct OscillateArgs
  {
    optional<json> oscillating;
  };
  void oscillate([[maybe_unused]] const OscillateArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "oscillate";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.oscillating) {
      cmd["service_data"]["oscillating"] = *_args.oscillating;
    }

    entity->wsConnSend(cmd);
  }

  // Set direction
  // Sets the fan rotation direction.
  struct SetDirectionArgs
  {
    optional<json> direction;
  };
  void setDirection([[maybe_unused]] const SetDirectionArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "set_direction";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.direction) {
      cmd["service_data"]["direction"] = *_args.direction;
    }

    entity->wsConnSend(cmd);
  }

  // Set speed
  // Sets the fan speed.
  struct SetPercentageArgs
  {
    optional<json> percentage;
  };
  void setPercentage([[maybe_unused]] const SetPercentageArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "set_percentage";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.percentage) {
      cmd["service_data"]["percentage"] = *_args.percentage;
    }

    entity->wsConnSend(cmd);
  }

  // Set preset mode
  // Sets preset mode.
  struct SetPresetModeArgs
  {
    optional<json> preset_mode;
  };
  void setPresetMode([[maybe_unused]] const SetPresetModeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "set_preset_mode";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.preset_mode) {
      cmd["service_data"]["preset_mode"] = *_args.preset_mode;
    }

    entity->wsConnSend(cmd);
  }

  // Toggle
  // Toggles the fan on/off.
  struct ToggleArgs
  {
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Turns fan off.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Turns fan on.
  struct TurnOnArgs
  {
    optional<json> percentage;
    optional<json> preset_mode;
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.percentage) {
      cmd["service_data"]["percentage"] = *_args.percentage;
    }
    if (_args.preset_mode) {
      cmd["service_data"]["preset_mode"] = *_args.preset_mode;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Ffmpeg

class Ffmpeg
{
public:
  Ffmpeg(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Ffmpeg;
  // Restart
  // Sends a restart command to a ffmpeg based sensor.
  struct RestartArgs
  {
    optional<json> entity_id;
  };
  void restart([[maybe_unused]] const RestartArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "ffmpeg";
    cmd["service"] = "restart";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.entity_id) {
      cmd["service_data"]["entity_id"] = *_args.entity_id;
    }

    entity->wsConnSend(cmd);
  }

  // Start
  // Sends a start command to a ffmpeg based sensor.
  struct StartArgs
  {
    optional<json> entity_id;
  };
  void start([[maybe_unused]] const StartArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "ffmpeg";
    cmd["service"] = "start";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.entity_id) {
      cmd["service_data"]["entity_id"] = *_args.entity_id;
    }

    entity->wsConnSend(cmd);
  }

  // Stop
  // Sends a stop command to a ffmpeg based sensor.
  struct StopArgs
  {
    optional<json> entity_id;
  };
  void stop([[maybe_unused]] const StopArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "ffmpeg";
    cmd["service"] = "stop";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.entity_id) {
      cmd["service_data"]["entity_id"] = *_args.entity_id;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Frontend

class Frontend
{
public:
  Frontend(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Frontend;
  // Reload themes
  // Reloads themes from the YAML-configuration.
  struct ReloadThemesArgs
  {
  };
  void reloadThemes([[maybe_unused]] const ReloadThemesArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "frontend";
    cmd["service"] = "reload_themes";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Set the default theme
  // Sets the default theme Home Assistant uses. Can be overridden by a user.
  struct SetThemeArgs
  {
    optional<json> mode;
    optional<json> name;
  };
  void setTheme([[maybe_unused]] const SetThemeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "frontend";
    cmd["service"] = "set_theme";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.mode) {
      cmd["service_data"]["mode"] = *_args.mode;
    }
    if (_args.name) {
      cmd["service_data"]["name"] = *_args.name;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Group

class Group
{
public:
  Group(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Group;
  // Reload
  // Reloads group configuration, entities, and notify services from YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "group";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Remove
  // Removes a group.
  struct RemoveArgs
  {
    optional<json> object_id;
  };
  void remove([[maybe_unused]] const RemoveArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "group";
    cmd["service"] = "remove";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.object_id) {
      cmd["service_data"]["object_id"] = *_args.object_id;
    }

    entity->wsConnSend(cmd);
  }

  // Set
  // Creates/Updates a user group.
  struct SetArgs
  {
    optional<json> add_entities;
    optional<json> all;
    optional<json> entities;
    optional<json> icon;
    optional<json> name;
    optional<json> object_id;
    optional<json> remove_entities;
  };
  void set([[maybe_unused]] const SetArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "group";
    cmd["service"] = "set";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.add_entities) {
      cmd["service_data"]["add_entities"] = *_args.add_entities;
    }
    if (_args.all) {
      cmd["service_data"]["all"] = *_args.all;
    }
    if (_args.entities) {
      cmd["service_data"]["entities"] = *_args.entities;
    }
    if (_args.icon) {
      cmd["service_data"]["icon"] = *_args.icon;
    }
    if (_args.name) {
      cmd["service_data"]["name"] = *_args.name;
    }
    if (_args.object_id) {
      cmd["service_data"]["object_id"] = *_args.object_id;
    }
    if (_args.remove_entities) {
      cmd["service_data"]["remove_entities"] = *_args.remove_entities;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Homeassistant

class Homeassistant
{
public:
  Homeassistant(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Homeassistant;
  // Check configuration
  // Checks the Home Assistant YAML-configuration files for errors. Errors will be shown in the Home Assistant logs.
  struct CheckConfigArgs
  {
  };
  void checkConfig([[maybe_unused]] const CheckConfigArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "check_config";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Reload all
  // Reload all YAML configuration that can be reloaded without restarting Home Assistant.
  struct ReloadAllArgs
  {
  };
  void reloadAll([[maybe_unused]] const ReloadAllArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "reload_all";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Reload config entry
  // Reloads the specified config entry.
  struct ReloadConfigEntryArgs
  {
    optional<json> entry_id;
  };
  void reloadConfigEntry([[maybe_unused]] const ReloadConfigEntryArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "reload_config_entry";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.entry_id) {
      cmd["service_data"]["entry_id"] = *_args.entry_id;
    }

    entity->wsConnSend(cmd);
  }

  // Reload core configuration
  // Reloads the core configuration from the YAML-configuration.
  struct ReloadCoreConfigArgs
  {
  };
  void reloadCoreConfig([[maybe_unused]] const ReloadCoreConfigArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "reload_core_config";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Reload custom Jinja2 templates
  // Reloads Jinja2 templates found in the `custom_templates` folder in your config. New values will be applied on the next render of the template.
  struct ReloadCustomTemplatesArgs
  {
  };
  void reloadCustomTemplates([[maybe_unused]] const ReloadCustomTemplatesArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "reload_custom_templates";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Restart
  // Restarts Home Assistant.
  struct RestartArgs
  {
  };
  void restart([[maybe_unused]] const RestartArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "restart";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Save persistent states
  // Saves the persistent states immediately. Maintains the normal periodic saving interval.
  struct SavePersistentStatesArgs
  {
  };
  void savePersistentStates([[maybe_unused]] const SavePersistentStatesArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "save_persistent_states";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Set location
  // Updates the Home Assistant location.
  struct SetLocationArgs
  {
    optional<json> elevation;
    optional<json> latitude;
    optional<json> longitude;
  };
  void setLocation([[maybe_unused]] const SetLocationArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "set_location";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.elevation) {
      cmd["service_data"]["elevation"] = *_args.elevation;
    }
    if (_args.latitude) {
      cmd["service_data"]["latitude"] = *_args.latitude;
    }
    if (_args.longitude) {
      cmd["service_data"]["longitude"] = *_args.longitude;
    }

    entity->wsConnSend(cmd);
  }

  // Stop
  // Stops Home Assistant.
  struct StopArgs
  {
  };
  void stop([[maybe_unused]] const StopArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "stop";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Generic toggle
  // Generic service to toggle devices on/off under any domain.
  struct ToggleArgs
  {
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Generic turn off
  // Generic service to turn devices off under any domain.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Generic turn on
  // Generic service to turn devices on under any domain.
  struct TurnOnArgs
  {
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Update entity
  // Forces one or more entities to update its data.
  struct UpdateEntityArgs
  {
  };
  void updateEntity([[maybe_unused]] const UpdateEntityArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "update_entity";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Humidifier

class Humidifier
{
public:
  Humidifier(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Humidifier;
  // Set humidity
  // Sets the target humidity.
  struct SetHumidityArgs
  {
    optional<json> humidity;
  };
  void setHumidity([[maybe_unused]] const SetHumidityArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "humidifier";
    cmd["service"] = "set_humidity";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.humidity) {
      cmd["service_data"]["humidity"] = *_args.humidity;
    }

    entity->wsConnSend(cmd);
  }

  // Set mode
  // Sets the humidifier operation mode.
  struct SetModeArgs
  {
    optional<json> mode;
  };
  void setMode([[maybe_unused]] const SetModeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "humidifier";
    cmd["service"] = "set_mode";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.mode) {
      cmd["service_data"]["mode"] = *_args.mode;
    }

    entity->wsConnSend(cmd);
  }

  // Toggle
  // Toggles the humidifier on/off.
  struct ToggleArgs
  {
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "humidifier";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Turns the humidifier off.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "humidifier";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Turns the humidifier on.
  struct TurnOnArgs
  {
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "humidifier";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR ImageProcessing

class ImageProcessing
{
public:
  ImageProcessing(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Image_processing;
  // Scan
  // Processes an image immediately.
  struct ScanArgs
  {
  };
  void scan([[maybe_unused]] const ScanArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "image_processing";
    cmd["service"] = "scan";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR InputBoolean

class InputBoolean
{
public:
  InputBoolean(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Input_boolean;
  // Reload
  // Reloads helpers from the YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_boolean";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Toggle
  // Toggles the helper on/off.
  struct ToggleArgs
  {
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_boolean";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Turns off the helper.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_boolean";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Turns on the helper.
  struct TurnOnArgs
  {
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_boolean";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR InputButton

class InputButton
{
public:
  InputButton(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Input_button;
  // Press
  // Mimics the physical button press on the device.
  struct PressArgs
  {
  };
  void press([[maybe_unused]] const PressArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_button";
    cmd["service"] = "press";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Reload
  // Reloads helpers from the YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_button";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR InputDatetime

class InputDatetime
{
public:
  InputDatetime(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Input_datetime;
  // Reload
  // Reloads helpers from the YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_datetime";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Set
  // Sets the date and/or time.
  struct SetDatetimeArgs
  {
    optional<json> date;
    optional<json> datetime;
    optional<json> time;
    optional<json> timestamp;
  };
  void setDatetime([[maybe_unused]] const SetDatetimeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_datetime";
    cmd["service"] = "set_datetime";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.date) {
      cmd["service_data"]["date"] = *_args.date;
    }
    if (_args.datetime) {
      cmd["service_data"]["datetime"] = *_args.datetime;
    }
    if (_args.time) {
      cmd["service_data"]["time"] = *_args.time;
    }
    if (_args.timestamp) {
      cmd["service_data"]["timestamp"] = *_args.timestamp;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR InputNumber

class InputNumber
{
public:
  InputNumber(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Input_number;
  // Decrement
  // Decrements the current value by 1 step.
  struct DecrementArgs
  {
  };
  void decrement([[maybe_unused]] const DecrementArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_number";
    cmd["service"] = "decrement";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Increment
  // Increments the value by 1 step.
  struct IncrementArgs
  {
  };
  void increment([[maybe_unused]] const IncrementArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_number";
    cmd["service"] = "increment";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Reload
  // Reloads helpers from the YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_number";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Set
  // Sets the value.
  struct SetValueArgs
  {
    optional<json> value;
  };
  void setValue([[maybe_unused]] const SetValueArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_number";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.value) {
      cmd["service_data"]["value"] = *_args.value;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR InputSelect

class InputSelect
{
public:
  InputSelect(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Input_select;
  // Reload
  // Reloads helpers from the YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // First
  // Selects the first option.
  struct SelectFirstArgs
  {
  };
  void selectFirst([[maybe_unused]] const SelectFirstArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "select_first";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Last
  // Selects the last option.
  struct SelectLastArgs
  {
  };
  void selectLast([[maybe_unused]] const SelectLastArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "select_last";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Next
  // Select the next option.
  struct SelectNextArgs
  {
    optional<json> cycle;
  };
  void selectNext([[maybe_unused]] const SelectNextArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "select_next";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.cycle) {
      cmd["service_data"]["cycle"] = *_args.cycle;
    }

    entity->wsConnSend(cmd);
  }

  // Select
  // Selects an option.
  struct SelectOptionArgs
  {
    optional<json> option;
  };
  void selectOption([[maybe_unused]] const SelectOptionArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "select_option";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.option) {
      cmd["service_data"]["option"] = *_args.option;
    }

    entity->wsConnSend(cmd);
  }

  // Previous
  // Selects the previous option.
  struct SelectPreviousArgs
  {
    optional<json> cycle;
  };
  void selectPrevious([[maybe_unused]] const SelectPreviousArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "select_previous";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.cycle) {
      cmd["service_data"]["cycle"] = *_args.cycle;
    }

    entity->wsConnSend(cmd);
  }

  // Set options
  // Sets the options.
  struct SetOptionsArgs
  {
    optional<json> options;
  };
  void setOptions([[maybe_unused]] const SetOptionsArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "set_options";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.options) {
      cmd["service_data"]["options"] = *_args.options;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR InputText

class InputText
{
public:
  InputText(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Input_text;
  // Reload
  // Reloads helpers from the YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_text";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Set
  // Sets the value.
  struct SetValueArgs
  {
    optional<json> value;
  };
  void setValue([[maybe_unused]] const SetValueArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_text";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.value) {
      cmd["service_data"]["value"] = *_args.value;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Light

class Light
{
public:
  Light(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Light;
  // Toggle
  // Toggles one or more lights, from on to off, or, off to on, based on their current state.
  struct ToggleArgs
  {
    optional<json> brightness;
    optional<json> brightness_pct;
    optional<json> color_name;
    optional<json> color_temp;
    optional<json> effect;
    optional<json> flash;
    optional<json> hs_color;
    optional<json> kelvin;
    optional<json> profile;
    optional<json> rgb_color;
    optional<json> transition;
    optional<json> white;
    optional<json> xy_color;
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "light";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.brightness) {
      cmd["service_data"]["brightness"] = *_args.brightness;
    }
    if (_args.brightness_pct) {
      cmd["service_data"]["brightness_pct"] = *_args.brightness_pct;
    }
    if (_args.color_name) {
      cmd["service_data"]["color_name"] = *_args.color_name;
    }
    if (_args.color_temp) {
      cmd["service_data"]["color_temp"] = *_args.color_temp;
    }
    if (_args.effect) {
      cmd["service_data"]["effect"] = *_args.effect;
    }
    if (_args.flash) {
      cmd["service_data"]["flash"] = *_args.flash;
    }
    if (_args.hs_color) {
      cmd["service_data"]["hs_color"] = *_args.hs_color;
    }
    if (_args.kelvin) {
      cmd["service_data"]["kelvin"] = *_args.kelvin;
    }
    if (_args.profile) {
      cmd["service_data"]["profile"] = *_args.profile;
    }
    if (_args.rgb_color) {
      cmd["service_data"]["rgb_color"] = *_args.rgb_color;
    }
    if (_args.transition) {
      cmd["service_data"]["transition"] = *_args.transition;
    }
    if (_args.white) {
      cmd["service_data"]["white"] = *_args.white;
    }
    if (_args.xy_color) {
      cmd["service_data"]["xy_color"] = *_args.xy_color;
    }

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Turn off one or more lights.
  struct TurnOffArgs
  {
    optional<json> flash;
    optional<json> transition;
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "light";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.flash) {
      cmd["service_data"]["flash"] = *_args.flash;
    }
    if (_args.transition) {
      cmd["service_data"]["transition"] = *_args.transition;
    }

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Turn on one or more lights and adjust properties of the light, even when they are turned on already.
  struct TurnOnArgs
  {
    optional<json> brightness;
    optional<json> brightness_pct;
    optional<json> brightness_step;
    optional<json> brightness_step_pct;
    optional<json> color_name;
    optional<json> color_temp;
    optional<json> effect;
    optional<json> flash;
    optional<json> hs_color;
    optional<json> kelvin;
    optional<json> profile;
    optional<json> rgb_color;
    optional<json> rgbw_color;
    optional<json> rgbww_color;
    optional<json> transition;
    optional<json> white;
    optional<json> xy_color;
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "light";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.brightness) {
      cmd["service_data"]["brightness"] = *_args.brightness;
    }
    if (_args.brightness_pct) {
      cmd["service_data"]["brightness_pct"] = *_args.brightness_pct;
    }
    if (_args.brightness_step) {
      cmd["service_data"]["brightness_step"] = *_args.brightness_step;
    }
    if (_args.brightness_step_pct) {
      cmd["service_data"]["brightness_step_pct"] = *_args.brightness_step_pct;
    }
    if (_args.color_name) {
      cmd["service_data"]["color_name"] = *_args.color_name;
    }
    if (_args.color_temp) {
      cmd["service_data"]["color_temp"] = *_args.color_temp;
    }
    if (_args.effect) {
      cmd["service_data"]["effect"] = *_args.effect;
    }
    if (_args.flash) {
      cmd["service_data"]["flash"] = *_args.flash;
    }
    if (_args.hs_color) {
      cmd["service_data"]["hs_color"] = *_args.hs_color;
    }
    if (_args.kelvin) {
      cmd["service_data"]["kelvin"] = *_args.kelvin;
    }
    if (_args.profile) {
      cmd["service_data"]["profile"] = *_args.profile;
    }
    if (_args.rgb_color) {
      cmd["service_data"]["rgb_color"] = *_args.rgb_color;
    }
    if (_args.rgbw_color) {
      cmd["service_data"]["rgbw_color"] = *_args.rgbw_color;
    }
    if (_args.rgbww_color) {
      cmd["service_data"]["rgbww_color"] = *_args.rgbww_color;
    }
    if (_args.transition) {
      cmd["service_data"]["transition"] = *_args.transition;
    }
    if (_args.white) {
      cmd["service_data"]["white"] = *_args.white;
    }
    if (_args.xy_color) {
      cmd["service_data"]["xy_color"] = *_args.xy_color;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Lock

class Lock
{
public:
  Lock(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Lock;
  // Lock
  // Locks a lock.
  struct LockArgs
  {
    optional<json> code;
  };
  void lock([[maybe_unused]] const LockArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "lock";
    cmd["service"] = "lock";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.code) {
      cmd["service_data"]["code"] = *_args.code;
    }

    entity->wsConnSend(cmd);
  }

  // Open
  // Opens a lock.
  struct OpenArgs
  {
    optional<json> code;
  };
  void open([[maybe_unused]] const OpenArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "lock";
    cmd["service"] = "open";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.code) {
      cmd["service_data"]["code"] = *_args.code;
    }

    entity->wsConnSend(cmd);
  }

  // Unlock
  // Unlocks a lock.
  struct UnlockArgs
  {
    optional<json> code;
  };
  void unlock([[maybe_unused]] const UnlockArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "lock";
    cmd["service"] = "unlock";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.code) {
      cmd["service_data"]["code"] = *_args.code;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Logbook

class Logbook
{
public:
  Logbook(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Logbook;
  // Log
  // Creates a custom entry in the logbook.
  struct LogArgs
  {
    optional<json> domain;
    optional<json> entity_id;
    optional<json> message;
    optional<json> name;
  };
  void log([[maybe_unused]] const LogArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "logbook";
    cmd["service"] = "log";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.domain) {
      cmd["service_data"]["domain"] = *_args.domain;
    }
    if (_args.entity_id) {
      cmd["service_data"]["entity_id"] = *_args.entity_id;
    }
    if (_args.message) {
      cmd["service_data"]["message"] = *_args.message;
    }
    if (_args.name) {
      cmd["service_data"]["name"] = *_args.name;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Logger

class Logger
{
public:
  Logger(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Logger;
  // Set default level
  // Sets the default log level for integrations.
  struct SetDefaultLevelArgs
  {
    optional<json> level;
  };
  void setDefaultLevel([[maybe_unused]] const SetDefaultLevelArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "logger";
    cmd["service"] = "set_default_level";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.level) {
      cmd["service_data"]["level"] = *_args.level;
    }

    entity->wsConnSend(cmd);
  }

  // Set level
  // Sets the log level for one or more integrations.
  struct SetLevelArgs
  {
  };
  void setLevel([[maybe_unused]] const SetLevelArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "logger";
    cmd["service"] = "set_level";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR MediaPlayer

class MediaPlayer
{
public:
  MediaPlayer(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Media_player;
  // Clear playlist
  // Clears the playlist.
  struct ClearPlaylistArgs
  {
  };
  void clearPlaylist([[maybe_unused]] const ClearPlaylistArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "clear_playlist";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Join
  // Groups media players together for synchronous playback. Only works on supported multiroom audio systems.
  struct JoinArgs
  {
    optional<json> group_members;
  };
  void join([[maybe_unused]] const JoinArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "join";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.group_members) {
      cmd["service_data"]["group_members"] = *_args.group_members;
    }

    entity->wsConnSend(cmd);
  }

  // Next
  // Selects the next track.
  struct MediaNextTrackArgs
  {
  };
  void mediaNextTrack([[maybe_unused]] const MediaNextTrackArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_next_track";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Pause
  // Pauses.
  struct MediaPauseArgs
  {
  };
  void mediaPause([[maybe_unused]] const MediaPauseArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_pause";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Play
  // Starts playing.
  struct MediaPlayArgs
  {
  };
  void mediaPlay([[maybe_unused]] const MediaPlayArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_play";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Play/Pause
  // Toggles play/pause.
  struct MediaPlayPauseArgs
  {
  };
  void mediaPlayPause([[maybe_unused]] const MediaPlayPauseArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_play_pause";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Previous
  // Selects the previous track.
  struct MediaPreviousTrackArgs
  {
  };
  void mediaPreviousTrack([[maybe_unused]] const MediaPreviousTrackArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_previous_track";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Seek
  // Allows you to go to a different part of the media that is currently playing.
  struct MediaSeekArgs
  {
    optional<json> seek_position;
  };
  void mediaSeek([[maybe_unused]] const MediaSeekArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_seek";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.seek_position) {
      cmd["service_data"]["seek_position"] = *_args.seek_position;
    }

    entity->wsConnSend(cmd);
  }

  // Stop
  // Stops playing.
  struct MediaStopArgs
  {
  };
  void mediaStop([[maybe_unused]] const MediaStopArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_stop";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Play media
  // Starts playing specified media.
  struct PlayMediaArgs
  {
    optional<json> announce;
    optional<json> enqueue;
    optional<json> media_content_id;
    optional<json> media_content_type;
  };
  void playMedia([[maybe_unused]] const PlayMediaArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "play_media";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.announce) {
      cmd["service_data"]["announce"] = *_args.announce;
    }
    if (_args.enqueue) {
      cmd["service_data"]["enqueue"] = *_args.enqueue;
    }
    if (_args.media_content_id) {
      cmd["service_data"]["media_content_id"] = *_args.media_content_id;
    }
    if (_args.media_content_type) {
      cmd["service_data"]["media_content_type"] = *_args.media_content_type;
    }

    entity->wsConnSend(cmd);
  }

  // Repeat
  // Playback mode that plays the media in a loop.
  struct RepeatSetArgs
  {
    optional<json> repeat;
  };
  void repeatSet([[maybe_unused]] const RepeatSetArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "repeat_set";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.repeat) {
      cmd["service_data"]["repeat"] = *_args.repeat;
    }

    entity->wsConnSend(cmd);
  }

  // Select sound mode
  // Selects a specific sound mode.
  struct SelectSoundModeArgs
  {
    optional<json> sound_mode;
  };
  void selectSoundMode([[maybe_unused]] const SelectSoundModeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "select_sound_mode";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.sound_mode) {
      cmd["service_data"]["sound_mode"] = *_args.sound_mode;
    }

    entity->wsConnSend(cmd);
  }

  // Select source
  // Sends the media player the command to change input source.
  struct SelectSourceArgs
  {
    optional<json> source;
  };
  void selectSource([[maybe_unused]] const SelectSourceArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "select_source";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.source) {
      cmd["service_data"]["source"] = *_args.source;
    }

    entity->wsConnSend(cmd);
  }

  // Shuffle
  // Playback mode that selects the media in randomized order.
  struct ShuffleSetArgs
  {
    optional<json> shuffle;
  };
  void shuffleSet([[maybe_unused]] const ShuffleSetArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "shuffle_set";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.shuffle) {
      cmd["service_data"]["shuffle"] = *_args.shuffle;
    }

    entity->wsConnSend(cmd);
  }

  // Toggle
  // Toggles a media player on/off.
  struct ToggleArgs
  {
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Turns off the power of the media player.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Turns on the power of the media player.
  struct TurnOnArgs
  {
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Unjoin
  // Removes the player from a group. Only works on platforms which support player groups.
  struct UnjoinArgs
  {
  };
  void unjoin([[maybe_unused]] const UnjoinArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "unjoin";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn down volume
  // Turns down the volume.
  struct VolumeDownArgs
  {
  };
  void volumeDown([[maybe_unused]] const VolumeDownArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "volume_down";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Mute/unmute volume
  // Mutes or unmutes the media player.
  struct VolumeMuteArgs
  {
    optional<json> is_volume_muted;
  };
  void volumeMute([[maybe_unused]] const VolumeMuteArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "volume_mute";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.is_volume_muted) {
      cmd["service_data"]["is_volume_muted"] = *_args.is_volume_muted;
    }

    entity->wsConnSend(cmd);
  }

  // Set volume
  // Sets the volume level.
  struct VolumeSetArgs
  {
    optional<json> volume_level;
  };
  void volumeSet([[maybe_unused]] const VolumeSetArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "volume_set";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.volume_level) {
      cmd["service_data"]["volume_level"] = *_args.volume_level;
    }

    entity->wsConnSend(cmd);
  }

  // Turn up volume
  // Turns up the volume.
  struct VolumeUpArgs
  {
  };
  void volumeUp([[maybe_unused]] const VolumeUpArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "volume_up";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Notify

class Notify
{
public:
  Notify(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Notify;
  // Send a notification via demo_test_target_name
  // Sends a notification message using the demo_test_target_name integration.
  struct DemoTestTargetNameArgs
  {
    optional<json> data;
    optional<json> message;
    optional<json> target;
    optional<json> title;
  };
  void demoTestTargetName([[maybe_unused]] const DemoTestTargetNameArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "notify";
    cmd["service"] = "demo_test_target_name";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.data) {
      cmd["service_data"]["data"] = *_args.data;
    }
    if (_args.message) {
      cmd["service_data"]["message"] = *_args.message;
    }
    if (_args.target) {
      cmd["service_data"]["target"] = *_args.target;
    }
    if (_args.title) {
      cmd["service_data"]["title"] = *_args.title;
    }

    entity->wsConnSend(cmd);
  }

  // Send a notification with notify
  // Sends a notification message using the notify service.
  struct NotifyArgs
  {
    optional<json> data;
    optional<json> message;
    optional<json> target;
    optional<json> title;
  };
  void notify([[maybe_unused]] const NotifyArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "notify";
    cmd["service"] = "notify";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.data) {
      cmd["service_data"]["data"] = *_args.data;
    }
    if (_args.message) {
      cmd["service_data"]["message"] = *_args.message;
    }
    if (_args.target) {
      cmd["service_data"]["target"] = *_args.target;
    }
    if (_args.title) {
      cmd["service_data"]["title"] = *_args.title;
    }

    entity->wsConnSend(cmd);
  }

  // Send a persistent notification
  // Sends a notification that is visible in the **Notifications** panel.
  struct PersistentNotificationArgs
  {
    optional<json> data;
    optional<json> message;
    optional<json> title;
  };
  void persistentNotification([[maybe_unused]] const PersistentNotificationArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "notify";
    cmd["service"] = "persistent_notification";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.data) {
      cmd["service_data"]["data"] = *_args.data;
    }
    if (_args.message) {
      cmd["service_data"]["message"] = *_args.message;
    }
    if (_args.title) {
      cmd["service_data"]["title"] = *_args.title;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Number

class Number
{
public:
  Number(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Number;
  // Set
  // Sets the value of a number.
  struct SetValueArgs
  {
    optional<json> value;
  };
  void setValue([[maybe_unused]] const SetValueArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "number";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.value) {
      cmd["service_data"]["value"] = *_args.value;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR PersistentNotification

class PersistentNotification
{
public:
  PersistentNotification(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Persistent_notification;
  // Create
  // Shows a notification on the **Notifications** panel.
  struct CreateArgs
  {
    optional<json> message;
    optional<json> notification_id;
    optional<json> title;
  };
  void create([[maybe_unused]] const CreateArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "persistent_notification";
    cmd["service"] = "create";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.message) {
      cmd["service_data"]["message"] = *_args.message;
    }
    if (_args.notification_id) {
      cmd["service_data"]["notification_id"] = *_args.notification_id;
    }
    if (_args.title) {
      cmd["service_data"]["title"] = *_args.title;
    }

    entity->wsConnSend(cmd);
  }

  // Dismiss
  // Removes a notification from the **Notifications** panel.
  struct DismissArgs
  {
    optional<json> notification_id;
  };
  void dismiss([[maybe_unused]] const DismissArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "persistent_notification";
    cmd["service"] = "dismiss";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.notification_id) {
      cmd["service_data"]["notification_id"] = *_args.notification_id;
    }

    entity->wsConnSend(cmd);
  }

  // Dismiss all
  // Removes all notifications from the **Notifications** panel.
  struct DismissAllArgs
  {
  };
  void dismissAll([[maybe_unused]] const DismissAllArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "persistent_notification";
    cmd["service"] = "dismiss_all";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Person

class Person
{
public:
  Person(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Person;
  // Reload
  // Reloads persons from the YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "person";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Recorder

class Recorder
{
public:
  Recorder(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Recorder;
  // Disable
  // Stops the recording of events and state changes.
  struct DisableArgs
  {
  };
  void disable([[maybe_unused]] const DisableArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "recorder";
    cmd["service"] = "disable";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Enable
  // Starts the recording of events and state changes.
  struct EnableArgs
  {
  };
  void enable([[maybe_unused]] const EnableArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "recorder";
    cmd["service"] = "enable";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Purge
  // Starts purge task - to clean up old data from your database.
  struct PurgeArgs
  {
    optional<json> apply_filter;
    optional<json> keep_days;
    optional<json> repack;
  };
  void purge([[maybe_unused]] const PurgeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "recorder";
    cmd["service"] = "purge";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.apply_filter) {
      cmd["service_data"]["apply_filter"] = *_args.apply_filter;
    }
    if (_args.keep_days) {
      cmd["service_data"]["keep_days"] = *_args.keep_days;
    }
    if (_args.repack) {
      cmd["service_data"]["repack"] = *_args.repack;
    }

    entity->wsConnSend(cmd);
  }

  // Purge entities
  // Starts a purge task to remove the data related to specific entities from your database.
  struct PurgeEntitiesArgs
  {
    optional<json> domains;
    optional<json> entity_globs;
    optional<json> keep_days;
  };
  void purgeEntities([[maybe_unused]] const PurgeEntitiesArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "recorder";
    cmd["service"] = "purge_entities";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.domains) {
      cmd["service_data"]["domains"] = *_args.domains;
    }
    if (_args.entity_globs) {
      cmd["service_data"]["entity_globs"] = *_args.entity_globs;
    }
    if (_args.keep_days) {
      cmd["service_data"]["keep_days"] = *_args.keep_days;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Scene

class Scene
{
public:
  Scene(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Scene;
  // Apply
  // Activates a scene with configuration.
  struct ApplyArgs
  {
    optional<json> entities;
    optional<json> transition;
  };
  void apply([[maybe_unused]] const ApplyArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "scene";
    cmd["service"] = "apply";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.entities) {
      cmd["service_data"]["entities"] = *_args.entities;
    }
    if (_args.transition) {
      cmd["service_data"]["transition"] = *_args.transition;
    }

    entity->wsConnSend(cmd);
  }

  // Create
  // Creates a new scene.
  struct CreateArgs
  {
    optional<json> entities;
    optional<json> scene_id;
    optional<json> snapshot_entities;
  };
  void create([[maybe_unused]] const CreateArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "scene";
    cmd["service"] = "create";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.entities) {
      cmd["service_data"]["entities"] = *_args.entities;
    }
    if (_args.scene_id) {
      cmd["service_data"]["scene_id"] = *_args.scene_id;
    }
    if (_args.snapshot_entities) {
      cmd["service_data"]["snapshot_entities"] = *_args.snapshot_entities;
    }

    entity->wsConnSend(cmd);
  }

  // Delete
  // Deletes a dynamically created scene.
  struct DeleteArgs
  {
  };
  void deleteScene([[maybe_unused]] const DeleteArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "scene";
    cmd["service"] = "delete";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Reload
  // Reloads the scenes from the YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "scene";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Activate
  // Activates a scene.
  struct TurnOnArgs
  {
    optional<json> transition;
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "scene";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.transition) {
      cmd["service_data"]["transition"] = *_args.transition;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Schedule

class Schedule
{
public:
  Schedule(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Schedule;
  // Reload
  // Reloads schedules from the YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "schedule";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Script

class Script
{
public:
  Script(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Script;
  // Reload
  // Reloads all the available scripts.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "script";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Toggle
  // Toggle a script. Starts it, if isn't running, stops it otherwise.
  struct ToggleArgs
  {
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "script";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Stops a running script.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "script";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Runs the sequence of actions defined in a script.
  struct TurnOnArgs
  {
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "script";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Select

class Select
{
public:
  Select(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Select;
  // First
  // Selects the first option.
  struct SelectFirstArgs
  {
  };
  void selectFirst([[maybe_unused]] const SelectFirstArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "select";
    cmd["service"] = "select_first";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Last
  // Selects the last option.
  struct SelectLastArgs
  {
  };
  void selectLast([[maybe_unused]] const SelectLastArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "select";
    cmd["service"] = "select_last";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Next
  // Selects the next option.
  struct SelectNextArgs
  {
    optional<json> cycle;
  };
  void selectNext([[maybe_unused]] const SelectNextArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "select";
    cmd["service"] = "select_next";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.cycle) {
      cmd["service_data"]["cycle"] = *_args.cycle;
    }

    entity->wsConnSend(cmd);
  }

  // Select
  // Selects an option.
  struct SelectOptionArgs
  {
    optional<json> option;
  };
  void selectOption([[maybe_unused]] const SelectOptionArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "select";
    cmd["service"] = "select_option";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.option) {
      cmd["service_data"]["option"] = *_args.option;
    }

    entity->wsConnSend(cmd);
  }

  // Previous
  // Selects the previous option.
  struct SelectPreviousArgs
  {
    optional<json> cycle;
  };
  void selectPrevious([[maybe_unused]] const SelectPreviousArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "select";
    cmd["service"] = "select_previous";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.cycle) {
      cmd["service_data"]["cycle"] = *_args.cycle;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR ShoppingList

class ShoppingList
{
public:
  ShoppingList(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Shopping_list;
  // Add item
  // Adds an item to the shopping list.
  struct AddItemArgs
  {
    optional<json> name;
  };
  void addItem([[maybe_unused]] const AddItemArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "add_item";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.name) {
      cmd["service_data"]["name"] = *_args.name;
    }

    entity->wsConnSend(cmd);
  }

  // Clear completed items
  // Clears completed items from the shopping list.
  struct ClearCompletedItemsArgs
  {
  };
  void clearCompletedItems([[maybe_unused]] const ClearCompletedItemsArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "clear_completed_items";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Complete all
  // Marks all items as completed in the shopping list (without removing them from the list).
  struct CompleteAllArgs
  {
  };
  void completeAll([[maybe_unused]] const CompleteAllArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "complete_all";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Complete item
  // Marks the first item with matching name as completed in the shopping list.
  struct CompleteItemArgs
  {
    optional<json> name;
  };
  void completeItem([[maybe_unused]] const CompleteItemArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "complete_item";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.name) {
      cmd["service_data"]["name"] = *_args.name;
    }

    entity->wsConnSend(cmd);
  }

  // Incomplete all
  // Marks all items as incomplete in the shopping list.
  struct IncompleteAllArgs
  {
  };
  void incompleteAll([[maybe_unused]] const IncompleteAllArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "incomplete_all";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Incomplete item
  // Marks the first item with matching name as incomplete in the shopping list.
  struct IncompleteItemArgs
  {
    optional<json> name;
  };
  void incompleteItem([[maybe_unused]] const IncompleteItemArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "incomplete_item";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.name) {
      cmd["service_data"]["name"] = *_args.name;
    }

    entity->wsConnSend(cmd);
  }

  // Remove item
  // Removes the first item with matching name from the shopping list.
  struct RemoveItemArgs
  {
    optional<json> name;
  };
  void removeItem([[maybe_unused]] const RemoveItemArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "remove_item";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.name) {
      cmd["service_data"]["name"] = *_args.name;
    }

    entity->wsConnSend(cmd);
  }

  // Sort all items
  // Sorts all items by name in the shopping list.
  struct SortArgs
  {
    optional<json> reverse;
  };
  void sort([[maybe_unused]] const SortArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "sort";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.reverse) {
      cmd["service_data"]["reverse"] = *_args.reverse;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Siren

class Siren
{
public:
  Siren(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Siren;
  // Toggle
  // Toggles the siren on/off.
  struct ToggleArgs
  {
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "siren";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Turns the siren off.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "siren";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Turns the siren on.
  struct TurnOnArgs
  {
    optional<json> duration;
    optional<json> tone;
    optional<json> volume_level;
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "siren";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.duration) {
      cmd["service_data"]["duration"] = *_args.duration;
    }
    if (_args.tone) {
      cmd["service_data"]["tone"] = *_args.tone;
    }
    if (_args.volume_level) {
      cmd["service_data"]["volume_level"] = *_args.volume_level;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Switch

class Switch
{
public:
  Switch(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Switch;
  // Toggle
  // Toggles a switch on/off.
  struct ToggleArgs
  {
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "switch";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Turns a switch off.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "switch";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Turns a switch on.
  struct TurnOnArgs
  {
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "switch";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR SystemLog

class SystemLog
{
public:
  SystemLog(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::System_log;
  // Clear all
  // Clears all log entries.
  struct ClearArgs
  {
  };
  void clear([[maybe_unused]] const ClearArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "system_log";
    cmd["service"] = "clear";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Write
  // Write log entry.
  struct WriteArgs
  {
    optional<json> level;
    optional<json> logger;
    optional<json> message;
  };
  void write([[maybe_unused]] const WriteArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "system_log";
    cmd["service"] = "write";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.level) {
      cmd["service_data"]["level"] = *_args.level;
    }
    if (_args.logger) {
      cmd["service_data"]["logger"] = *_args.logger;
    }
    if (_args.message) {
      cmd["service_data"]["message"] = *_args.message;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Text

class Text
{
public:
  Text(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Text;
  // Set value
  // Sets the value.
  struct SetValueArgs
  {
    optional<json> value;
  };
  void setValue([[maybe_unused]] const SetValueArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "text";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.value) {
      cmd["service_data"]["value"] = *_args.value;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Time

class Time
{
public:
  Time(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Time;
  // Set Time
  // Sets the time.
  struct SetValueArgs
  {
    optional<json> time;
  };
  void setValue([[maybe_unused]] const SetValueArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "time";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.time) {
      cmd["service_data"]["time"] = *_args.time;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Timer

class Timer
{
public:
  Timer(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Timer;
  // Cancel
  // Cancels a timer.
  struct CancelArgs
  {
  };
  void cancel([[maybe_unused]] const CancelArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "cancel";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Change
  // Changes a timer.
  struct ChangeArgs
  {
    optional<json> duration;
  };
  void change([[maybe_unused]] const ChangeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "change";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.duration) {
      cmd["service_data"]["duration"] = *_args.duration;
    }

    entity->wsConnSend(cmd);
  }

  // Finish
  // Finishes a timer.
  struct FinishArgs
  {
  };
  void finish([[maybe_unused]] const FinishArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "finish";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Pause
  // Pauses a timer.
  struct PauseArgs
  {
  };
  void pause([[maybe_unused]] const PauseArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "pause";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Reload
  // Reloads timers from the YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Start
  // Starts a timer.
  struct StartArgs
  {
    optional<json> duration;
  };
  void start([[maybe_unused]] const StartArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "start";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.duration) {
      cmd["service_data"]["duration"] = *_args.duration;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Todo

class Todo
{
public:
  Todo(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Todo;
  // Add to-do list item
  // Add a new to-do list item.
  struct AddItemArgs
  {
    optional<json> description;
    optional<json> due_date;
    optional<json> due_datetime;
    optional<json> item;
  };
  void addItem([[maybe_unused]] const AddItemArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "todo";
    cmd["service"] = "add_item";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.description) {
      cmd["service_data"]["description"] = *_args.description;
    }
    if (_args.due_date) {
      cmd["service_data"]["due_date"] = *_args.due_date;
    }
    if (_args.due_datetime) {
      cmd["service_data"]["due_datetime"] = *_args.due_datetime;
    }
    if (_args.item) {
      cmd["service_data"]["item"] = *_args.item;
    }

    entity->wsConnSend(cmd);
  }

  // Get to-do list items
  // Get items on a to-do list.
  struct GetItemsArgs
  {
    optional<json> status;
  };
  void getItems([[maybe_unused]] const GetItemsArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "todo";
    cmd["service"] = "get_items";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.status) {
      cmd["service_data"]["status"] = *_args.status;
    }

    entity->wsConnSend(cmd);
  }

  // Remove all completed to-do list items
  // Remove all to-do list items that have been completed.
  struct RemoveCompletedItemsArgs
  {
  };
  void removeCompletedItems([[maybe_unused]] const RemoveCompletedItemsArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "todo";
    cmd["service"] = "remove_completed_items";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Remove a to-do list item
  // Remove an existing to-do list item by its name.
  struct RemoveItemArgs
  {
    optional<json> item;
  };
  void removeItem([[maybe_unused]] const RemoveItemArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "todo";
    cmd["service"] = "remove_item";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.item) {
      cmd["service_data"]["item"] = *_args.item;
    }

    entity->wsConnSend(cmd);
  }

  // Update to-do list item
  // Update an existing to-do list item based on its name.
  struct UpdateItemArgs
  {
    optional<json> description;
    optional<json> due_date;
    optional<json> due_datetime;
    optional<json> item;
    optional<json> rename;
    optional<json> status;
  };
  void updateItem([[maybe_unused]] const UpdateItemArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "todo";
    cmd["service"] = "update_item";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.description) {
      cmd["service_data"]["description"] = *_args.description;
    }
    if (_args.due_date) {
      cmd["service_data"]["due_date"] = *_args.due_date;
    }
    if (_args.due_datetime) {
      cmd["service_data"]["due_datetime"] = *_args.due_datetime;
    }
    if (_args.item) {
      cmd["service_data"]["item"] = *_args.item;
    }
    if (_args.rename) {
      cmd["service_data"]["rename"] = *_args.rename;
    }
    if (_args.status) {
      cmd["service_data"]["status"] = *_args.status;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Tts

class Tts
{
public:
  Tts(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Tts;
  // Clear TTS cache
  // Removes all cached text-to-speech files and purges the memory.
  struct ClearCacheArgs
  {
  };
  void clearCache([[maybe_unused]] const ClearCacheArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "tts";
    cmd["service"] = "clear_cache";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Say a TTS message with demo
  // Say something using text-to-speech on a media player with demo.
  struct DemoSayArgs
  {
    optional<json> cache;
    optional<json> entity_id;
    optional<json> language;
    optional<json> message;
    optional<json> options;
  };
  void demoSay([[maybe_unused]] const DemoSayArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "tts";
    cmd["service"] = "demo_say";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.cache) {
      cmd["service_data"]["cache"] = *_args.cache;
    }
    if (_args.entity_id) {
      cmd["service_data"]["entity_id"] = *_args.entity_id;
    }
    if (_args.language) {
      cmd["service_data"]["language"] = *_args.language;
    }
    if (_args.message) {
      cmd["service_data"]["message"] = *_args.message;
    }
    if (_args.options) {
      cmd["service_data"]["options"] = *_args.options;
    }

    entity->wsConnSend(cmd);
  }

  // Speak
  // Speaks something using text-to-speech on a media player.
  struct SpeakArgs
  {
    optional<json> cache;
    optional<json> language;
    optional<json> media_player_entity_id;
    optional<json> message;
    optional<json> options;
  };
  void speak([[maybe_unused]] const SpeakArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "tts";
    cmd["service"] = "speak";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.cache) {
      cmd["service_data"]["cache"] = *_args.cache;
    }
    if (_args.language) {
      cmd["service_data"]["language"] = *_args.language;
    }
    if (_args.media_player_entity_id) {
      cmd["service_data"]["media_player_entity_id"] = *_args.media_player_entity_id;
    }
    if (_args.message) {
      cmd["service_data"]["message"] = *_args.message;
    }
    if (_args.options) {
      cmd["service_data"]["options"] = *_args.options;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Update

class Update
{
public:
  Update(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Update;
  // Clear skipped update
  // Removes the skipped version marker from an update.
  struct ClearSkippedArgs
  {
  };
  void clearSkipped([[maybe_unused]] const ClearSkippedArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "update";
    cmd["service"] = "clear_skipped";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Install update
  // Installs an update for this device or service.
  struct InstallArgs
  {
    optional<json> backup;
    optional<json> version;
  };
  void install([[maybe_unused]] const InstallArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "update";
    cmd["service"] = "install";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.backup) {
      cmd["service_data"]["backup"] = *_args.backup;
    }
    if (_args.version) {
      cmd["service_data"]["version"] = *_args.version;
    }

    entity->wsConnSend(cmd);
  }

  // Skip update
  // Marks currently available update as skipped.
  struct SkipArgs
  {
  };
  void skip([[maybe_unused]] const SkipArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "update";
    cmd["service"] = "skip";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Vacuum

class Vacuum
{
public:
  Vacuum(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Vacuum;
  // Clean spot
  // Tells the vacuum cleaner to do a spot clean-up.
  struct CleanSpotArgs
  {
  };
  void cleanSpot([[maybe_unused]] const CleanSpotArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "clean_spot";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Locate
  // Locates the vacuum cleaner robot.
  struct LocateArgs
  {
  };
  void locate([[maybe_unused]] const LocateArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "locate";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Pause
  // Pauses the cleaning task.
  struct PauseArgs
  {
  };
  void pause([[maybe_unused]] const PauseArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "pause";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Return to dock
  // Tells the vacuum cleaner to return to its dock.
  struct ReturnToBaseArgs
  {
  };
  void returnToBase([[maybe_unused]] const ReturnToBaseArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "return_to_base";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Send command
  // Sends a command to the vacuum cleaner.
  struct SendCommandArgs
  {
    optional<json> command;
    optional<json> params;
  };
  void sendCommand([[maybe_unused]] const SendCommandArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "send_command";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.command) {
      cmd["service_data"]["command"] = *_args.command;
    }
    if (_args.params) {
      cmd["service_data"]["params"] = *_args.params;
    }

    entity->wsConnSend(cmd);
  }

  // Set fan speed
  // Sets the fan speed of the vacuum cleaner.
  struct SetFanSpeedArgs
  {
    optional<json> fan_speed;
  };
  void setFanSpeed([[maybe_unused]] const SetFanSpeedArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "set_fan_speed";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.fan_speed) {
      cmd["service_data"]["fan_speed"] = *_args.fan_speed;
    }

    entity->wsConnSend(cmd);
  }

  // Start
  // Starts or resumes the cleaning task.
  struct StartArgs
  {
  };
  void start([[maybe_unused]] const StartArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "start";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Start/pause
  // Starts, pauses, or resumes the cleaning task.
  struct StartPauseArgs
  {
  };
  void startPause([[maybe_unused]] const StartPauseArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "start_pause";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Stop
  // Stops the current cleaning task.
  struct StopArgs
  {
  };
  void stop([[maybe_unused]] const StopArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "stop";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Toggle
  // Toggles the vacuum cleaner on/off.
  struct ToggleArgs
  {
  };
  void toggle([[maybe_unused]] const ToggleArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Stops the current cleaning task and returns to its dock.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Starts a new cleaning task.
  struct TurnOnArgs
  {
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR WaterHeater

class WaterHeater
{
public:
  WaterHeater(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Water_heater;
  // Set away mode
  // Turns away mode on/off.
  struct SetAwayModeArgs
  {
    optional<json> away_mode;
  };
  void setAwayMode([[maybe_unused]] const SetAwayModeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "water_heater";
    cmd["service"] = "set_away_mode";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.away_mode) {
      cmd["service_data"]["away_mode"] = *_args.away_mode;
    }

    entity->wsConnSend(cmd);
  }

  // Set operation mode
  // Sets the operation mode.
  struct SetOperationModeArgs
  {
    optional<json> operation_mode;
  };
  void setOperationMode([[maybe_unused]] const SetOperationModeArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "water_heater";
    cmd["service"] = "set_operation_mode";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.operation_mode) {
      cmd["service_data"]["operation_mode"] = *_args.operation_mode;
    }

    entity->wsConnSend(cmd);
  }

  // Set temperature
  // Sets the target temperature.
  struct SetTemperatureArgs
  {
    optional<json> operation_mode;
    optional<json> temperature;
  };
  void setTemperature([[maybe_unused]] const SetTemperatureArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "water_heater";
    cmd["service"] = "set_temperature";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.operation_mode) {
      cmd["service_data"]["operation_mode"] = *_args.operation_mode;
    }
    if (_args.temperature) {
      cmd["service_data"]["temperature"] = *_args.temperature;
    }

    entity->wsConnSend(cmd);
  }

  // Turn off
  // Turns water heater off.
  struct TurnOffArgs
  {
  };
  void turnOff([[maybe_unused]] const TurnOffArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "water_heater";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

  // Turn on
  // Turns water heater on.
  struct TurnOnArgs
  {
  };
  void turnOn([[maybe_unused]] const TurnOnArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "water_heater";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Weather

class Weather
{
public:
  Weather(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Weather;
  // Get forecast
  // Get weather forecast.
  struct GetForecastArgs
  {
    optional<json> type;
  };
  void getForecast([[maybe_unused]] const GetForecastArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "weather";
    cmd["service"] = "get_forecast";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.type) {
      cmd["service_data"]["type"] = *_args.type;
    }

    entity->wsConnSend(cmd);
  }

  // Get forecasts
  // Get weather forecasts.
  struct GetForecastsArgs
  {
    optional<json> type;
  };
  void getForecasts([[maybe_unused]] const GetForecastsArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "weather";
    cmd["service"] = "get_forecasts";
    cmd["target"]["entity_id"] = entity->id;
    if (_args.type) {
      cmd["service_data"]["type"] = *_args.type;
    }

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

// START HEADER FOR Zone

class Zone
{
public:
  Zone(std::shared_ptr<HAEntity> _entity) :
    entity(_entity) {}

  // const EntityType __domain = EntityType::Zone;
  // Reload
  // Reloads zones from the YAML-configuration.
  struct ReloadArgs
  {
  };
  void reload([[maybe_unused]] const ReloadArgs& _args)
  {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "zone";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = entity->id;

    entity->wsConnSend(cmd);
  }

private:
  std::shared_ptr<HAEntity> entity;
};

}
