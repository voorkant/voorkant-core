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

// START HEADER FOR Alarm_control_panel

class Alarm_control_panel : HAEntity
{
  // const EntityType __domain = EntityType::Alarm_control_panel;
  // Arm away
  // Sets the alarm to: _armed, no one home_.
  struct alarm_arm_away_args
  {
    optional<json> code;
  };
  void alarm_arm_away(const alarm_arm_away_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_arm_away";
    cmd["target"]["entity_id"] = name;
    if (args.code) { cmd["service_data"]["code"] = *args.code; }

    backend->WSConnSend(cmd);
  }

  // Arm with custom bypass
  // Arms the alarm while allowing to bypass a custom area.
  struct alarm_arm_custom_bypass_args
  {
    optional<json> code;
  };
  void alarm_arm_custom_bypass(const alarm_arm_custom_bypass_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_arm_custom_bypass";
    cmd["target"]["entity_id"] = name;
    if (args.code) { cmd["service_data"]["code"] = *args.code; }

    backend->WSConnSend(cmd);
  }

  // Arm home
  // Sets the alarm to: _armed, but someone is home_.
  struct alarm_arm_home_args
  {
    optional<json> code;
  };
  void alarm_arm_home(const alarm_arm_home_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_arm_home";
    cmd["target"]["entity_id"] = name;
    if (args.code) { cmd["service_data"]["code"] = *args.code; }

    backend->WSConnSend(cmd);
  }

  // Arm night
  // Sets the alarm to: _armed for the night_.
  struct alarm_arm_night_args
  {
    optional<json> code;
  };
  void alarm_arm_night(const alarm_arm_night_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_arm_night";
    cmd["target"]["entity_id"] = name;
    if (args.code) { cmd["service_data"]["code"] = *args.code; }

    backend->WSConnSend(cmd);
  }

  // Arm vacation
  // Sets the alarm to: _armed for vacation_.
  struct alarm_arm_vacation_args
  {
    optional<json> code;
  };
  void alarm_arm_vacation(const alarm_arm_vacation_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_arm_vacation";
    cmd["target"]["entity_id"] = name;
    if (args.code) { cmd["service_data"]["code"] = *args.code; }

    backend->WSConnSend(cmd);
  }

  // Disarm
  // Disarms the alarm.
  struct alarm_disarm_args
  {
    optional<json> code;
  };
  void alarm_disarm(const alarm_disarm_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_disarm";
    cmd["target"]["entity_id"] = name;
    if (args.code) { cmd["service_data"]["code"] = *args.code; }

    backend->WSConnSend(cmd);
  }

  // Trigger
  // Enables an external alarm trigger.
  struct alarm_trigger_args
  {
    optional<json> code;
  };
  void alarm_trigger(const alarm_trigger_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "alarm_control_panel";
    cmd["service"] = "alarm_trigger";
    cmd["target"]["entity_id"] = name;
    if (args.code) { cmd["service_data"]["code"] = *args.code; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Automation

class Automation : HAEntity
{
  // const EntityType __domain = EntityType::Automation;
  // Reload
  // Reloads the automation configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "automation";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Toggle
  // Toggles (enable / disable) an automation.
  struct toggle_args
  {
  };
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "automation";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Trigger
  // Triggers the actions of an automation.
  struct trigger_args
  {
    optional<json> skip_condition;
  };
  void trigger(const trigger_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "automation";
    cmd["service"] = "trigger";
    cmd["target"]["entity_id"] = name;
    if (args.skip_condition) { cmd["service_data"]["skip_condition"] = *args.skip_condition; }

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Disables an automation.
  struct turn_off_args
  {
    optional<json> stop_actions;
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "automation";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;
    if (args.stop_actions) { cmd["service_data"]["stop_actions"] = *args.stop_actions; }

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Enables an automation.
  struct turn_on_args
  {
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "automation";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Backup

class Backup : HAEntity
{
  // const EntityType __domain = EntityType::Backup;
  // Create backup
  // Creates a new backup.
  struct create_args
  {
  };
  void create(const create_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "backup";
    cmd["service"] = "create";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Button

class Button : HAEntity
{
  // const EntityType __domain = EntityType::Button;
  // Press
  // Press the button entity.
  struct press_args
  {
  };
  void press(const press_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "button";
    cmd["service"] = "press";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Calendar

class Calendar : HAEntity
{
  // const EntityType __domain = EntityType::Calendar;
  // Create event
  // Adds a new calendar event.
  struct create_event_args
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
  void create_event(const create_event_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "calendar";
    cmd["service"] = "create_event";
    cmd["target"]["entity_id"] = name;
    if (args.description) { cmd["service_data"]["description"] = *args.description; }
    if (args.end_date) { cmd["service_data"]["end_date"] = *args.end_date; }
    if (args.end_date_time) { cmd["service_data"]["end_date_time"] = *args.end_date_time; }
    if (args.in) { cmd["service_data"]["in"] = *args.in; }
    if (args.location) { cmd["service_data"]["location"] = *args.location; }
    if (args.start_date) { cmd["service_data"]["start_date"] = *args.start_date; }
    if (args.start_date_time) { cmd["service_data"]["start_date_time"] = *args.start_date_time; }
    if (args.summary) { cmd["service_data"]["summary"] = *args.summary; }

    backend->WSConnSend(cmd);
  }

  // Get events
  // Get events on a calendar within a time range.
  struct get_events_args
  {
    optional<json> duration;
    optional<json> end_date_time;
    optional<json> start_date_time;
  };
  void get_events(const get_events_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "calendar";
    cmd["service"] = "get_events";
    cmd["target"]["entity_id"] = name;
    if (args.duration) { cmd["service_data"]["duration"] = *args.duration; }
    if (args.end_date_time) { cmd["service_data"]["end_date_time"] = *args.end_date_time; }
    if (args.start_date_time) { cmd["service_data"]["start_date_time"] = *args.start_date_time; }

    backend->WSConnSend(cmd);
  }

  // List event
  // Lists events on a calendar within a time range.
  struct list_events_args
  {
    optional<json> duration;
    optional<json> end_date_time;
    optional<json> start_date_time;
  };
  void list_events(const list_events_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "calendar";
    cmd["service"] = "list_events";
    cmd["target"]["entity_id"] = name;
    if (args.duration) { cmd["service_data"]["duration"] = *args.duration; }
    if (args.end_date_time) { cmd["service_data"]["end_date_time"] = *args.end_date_time; }
    if (args.start_date_time) { cmd["service_data"]["start_date_time"] = *args.start_date_time; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Camera

class Camera : HAEntity
{
  // const EntityType __domain = EntityType::Camera;
  // Disable motion detection
  // Disables the motion detection.
  struct disable_motion_detection_args
  {
  };
  void disable_motion_detection(const disable_motion_detection_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "disable_motion_detection";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Enable motion detection
  // Enables the motion detection.
  struct enable_motion_detection_args
  {
  };
  void enable_motion_detection(const enable_motion_detection_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "enable_motion_detection";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Play stream
  // Plays the camera stream on a supported media player.
  struct play_stream_args
  {
    optional<json> format;
    optional<json> media_player;
  };
  void play_stream(const play_stream_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "play_stream";
    cmd["target"]["entity_id"] = name;
    if (args.format) { cmd["service_data"]["format"] = *args.format; }
    if (args.media_player) { cmd["service_data"]["media_player"] = *args.media_player; }

    backend->WSConnSend(cmd);
  }

  // Record
  // Creates a recording of a live camera feed.
  struct record_args
  {
    optional<json> duration;
    optional<json> filename;
    optional<json> lookback;
  };
  void record(const record_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "record";
    cmd["target"]["entity_id"] = name;
    if (args.duration) { cmd["service_data"]["duration"] = *args.duration; }
    if (args.filename) { cmd["service_data"]["filename"] = *args.filename; }
    if (args.lookback) { cmd["service_data"]["lookback"] = *args.lookback; }

    backend->WSConnSend(cmd);
  }

  // Take snapshot
  // Takes a snapshot from a camera.
  struct snapshot_args
  {
    optional<json> filename;
  };
  void snapshot(const snapshot_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "snapshot";
    cmd["target"]["entity_id"] = name;
    if (args.filename) { cmd["service_data"]["filename"] = *args.filename; }

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Turns off the camera.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Turns on the camera.
  struct turn_on_args
  {
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "camera";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Climate

class Climate : HAEntity
{
  // const EntityType __domain = EntityType::Climate;
  // Turn on/off auxiliary heater
  // Turns auxiliary heater on/off.
  struct set_aux_heat_args
  {
    optional<json> aux_heat;
  };
  void set_aux_heat(const set_aux_heat_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_aux_heat";
    cmd["target"]["entity_id"] = name;
    if (args.aux_heat) { cmd["service_data"]["aux_heat"] = *args.aux_heat; }

    backend->WSConnSend(cmd);
  }

  // Set fan mode
  // Sets fan operation mode.
  struct set_fan_mode_args
  {
    optional<json> fan_mode;
  };
  void set_fan_mode(const set_fan_mode_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_fan_mode";
    cmd["target"]["entity_id"] = name;
    if (args.fan_mode) { cmd["service_data"]["fan_mode"] = *args.fan_mode; }

    backend->WSConnSend(cmd);
  }

  // Set target humidity
  // Sets target humidity.
  struct set_humidity_args
  {
    optional<json> humidity;
  };
  void set_humidity(const set_humidity_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_humidity";
    cmd["target"]["entity_id"] = name;
    if (args.humidity) { cmd["service_data"]["humidity"] = *args.humidity; }

    backend->WSConnSend(cmd);
  }

  // Set HVAC mode
  // Sets HVAC operation mode.
  struct set_hvac_mode_args
  {
    optional<json> hvac_mode;
  };
  void set_hvac_mode(const set_hvac_mode_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_hvac_mode";
    cmd["target"]["entity_id"] = name;
    if (args.hvac_mode) { cmd["service_data"]["hvac_mode"] = *args.hvac_mode; }

    backend->WSConnSend(cmd);
  }

  // Set preset mode
  // Sets preset mode.
  struct set_preset_mode_args
  {
    optional<json> preset_mode;
  };
  void set_preset_mode(const set_preset_mode_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_preset_mode";
    cmd["target"]["entity_id"] = name;
    if (args.preset_mode) { cmd["service_data"]["preset_mode"] = *args.preset_mode; }

    backend->WSConnSend(cmd);
  }

  // Set swing mode
  // Sets swing operation mode.
  struct set_swing_mode_args
  {
    optional<json> swing_mode;
  };
  void set_swing_mode(const set_swing_mode_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_swing_mode";
    cmd["target"]["entity_id"] = name;
    if (args.swing_mode) { cmd["service_data"]["swing_mode"] = *args.swing_mode; }

    backend->WSConnSend(cmd);
  }

  // Set target temperature
  // Sets target temperature.
  struct set_temperature_args
  {
    optional<json> hvac_mode;
    optional<json> target_temp_high;
    optional<json> target_temp_low;
    optional<json> temperature;
  };
  void set_temperature(const set_temperature_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "set_temperature";
    cmd["target"]["entity_id"] = name;
    if (args.hvac_mode) { cmd["service_data"]["hvac_mode"] = *args.hvac_mode; }
    if (args.target_temp_high) { cmd["service_data"]["target_temp_high"] = *args.target_temp_high; }
    if (args.target_temp_low) { cmd["service_data"]["target_temp_low"] = *args.target_temp_low; }
    if (args.temperature) { cmd["service_data"]["temperature"] = *args.temperature; }

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Turns climate device off.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Turns climate device on.
  struct turn_on_args
  {
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "climate";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Cloud

class Cloud : HAEntity
{
  // const EntityType __domain = EntityType::Cloud;
  // Remote connect
  // Makes the instance UI accessible from outside of the local network by using Home Assistant Cloud.
  struct remote_connect_args
  {
  };
  void remote_connect(const remote_connect_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cloud";
    cmd["service"] = "remote_connect";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Remote disconnect
  // Disconnects the Home Assistant UI from the Home Assistant Cloud. You will no longer be able to access your Home Assistant instance from outside your local network.
  struct remote_disconnect_args
  {
  };
  void remote_disconnect(const remote_disconnect_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cloud";
    cmd["service"] = "remote_disconnect";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Conversation

class Conversation : HAEntity
{
  // const EntityType __domain = EntityType::Conversation;
  // Process
  // Launches a conversation from a transcribed text.
  struct process_args
  {
    optional<json> agent_id;
    optional<json> language;
    optional<json> text;
  };
  void process(const process_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "conversation";
    cmd["service"] = "process";
    cmd["target"]["entity_id"] = name;
    if (args.agent_id) { cmd["service_data"]["agent_id"] = *args.agent_id; }
    if (args.language) { cmd["service_data"]["language"] = *args.language; }
    if (args.text) { cmd["service_data"]["text"] = *args.text; }

    backend->WSConnSend(cmd);
  }

  // Reload
  // Reloads the intent configuration.
  struct reload_args
  {
    optional<json> agent_id;
    optional<json> language;
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "conversation";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;
    if (args.agent_id) { cmd["service_data"]["agent_id"] = *args.agent_id; }
    if (args.language) { cmd["service_data"]["language"] = *args.language; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Counter

class Counter : HAEntity
{
  // const EntityType __domain = EntityType::Counter;
  // Decrement
  // Decrements a counter.
  struct decrement_args
  {
  };
  void decrement(const decrement_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "counter";
    cmd["service"] = "decrement";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Increment
  // Increments a counter.
  struct increment_args
  {
  };
  void increment(const increment_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "counter";
    cmd["service"] = "increment";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Reset
  // Resets a counter.
  struct reset_args
  {
  };
  void reset(const reset_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "counter";
    cmd["service"] = "reset";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Set
  // Sets the counter value.
  struct set_value_args
  {
    optional<json> value;
  };
  void set_value(const set_value_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "counter";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = name;
    if (args.value) { cmd["service_data"]["value"] = *args.value; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Cover

class Cover : HAEntity
{
  // const EntityType __domain = EntityType::Cover;
  // Close
  // Closes a cover.
  struct close_cover_args
  {
  };
  void close_cover(const close_cover_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "close_cover";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Close tilt
  // Tilts a cover to close.
  struct close_cover_tilt_args
  {
  };
  void close_cover_tilt(const close_cover_tilt_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "close_cover_tilt";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Open
  // Opens a cover.
  struct open_cover_args
  {
  };
  void open_cover(const open_cover_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "open_cover";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Open tilt
  // Tilts a cover open.
  struct open_cover_tilt_args
  {
  };
  void open_cover_tilt(const open_cover_tilt_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "open_cover_tilt";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Set position
  // Moves a cover to a specific position.
  struct set_cover_position_args
  {
    optional<json> position;
  };
  void set_cover_position(const set_cover_position_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "set_cover_position";
    cmd["target"]["entity_id"] = name;
    if (args.position) { cmd["service_data"]["position"] = *args.position; }

    backend->WSConnSend(cmd);
  }

  // Set tilt position
  // Moves a cover tilt to a specific position.
  struct set_cover_tilt_position_args
  {
    optional<json> tilt_position;
  };
  void set_cover_tilt_position(const set_cover_tilt_position_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "set_cover_tilt_position";
    cmd["target"]["entity_id"] = name;
    if (args.tilt_position) { cmd["service_data"]["tilt_position"] = *args.tilt_position; }

    backend->WSConnSend(cmd);
  }

  // Stop
  // Stops the cover movement.
  struct stop_cover_args
  {
  };
  void stop_cover(const stop_cover_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "stop_cover";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Stop tilt
  // Stops a tilting cover movement.
  struct stop_cover_tilt_args
  {
  };
  void stop_cover_tilt(const stop_cover_tilt_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "stop_cover_tilt";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Toggle
  // Toggles a cover open/closed.
  struct toggle_args
  {
  };
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Toggle tilt
  // Toggles a cover tilt open/closed.
  struct toggle_cover_tilt_args
  {
  };
  void toggle_cover_tilt(const toggle_cover_tilt_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "cover";
    cmd["service"] = "toggle_cover_tilt";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Date

class Date : HAEntity
{
  // const EntityType __domain = EntityType::Date;
  // Set date
  // Sets the date.
  struct set_value_args
  {
    optional<json> date;
  };
  void set_value(const set_value_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "date";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = name;
    if (args.date) { cmd["service_data"]["date"] = *args.date; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Datetime

class Datetime : HAEntity
{
  // const EntityType __domain = EntityType::Datetime;
  // Set date/time
  // Sets the date/time for a datetime entity.
  struct set_value_args
  {
    optional<json> datetime;
  };
  void set_value(const set_value_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "datetime";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = name;
    if (args.datetime) { cmd["service_data"]["datetime"] = *args.datetime; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Demo

class Demo : HAEntity
{
  // const EntityType __domain = EntityType::Demo;
  // Randomize device tracker data
  // Demonstrates using a device tracker to see where devices are located.
  struct randomize_device_tracker_data_args
  {
  };
  void randomize_device_tracker_data(const randomize_device_tracker_data_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "demo";
    cmd["service"] = "randomize_device_tracker_data";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Device_tracker

class Device_tracker : HAEntity
{
  // const EntityType __domain = EntityType::Device_tracker;
  // See
  // Records a seen tracked device.
  struct see_args
  {
    optional<json> battery;
    optional<json> dev_id;
    optional<json> gps;
    optional<json> gps_accuracy;
    optional<json> host_name;
    optional<json> location_name;
    optional<json> mac;
  };
  void see(const see_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "device_tracker";
    cmd["service"] = "see";
    cmd["target"]["entity_id"] = name;
    if (args.battery) { cmd["service_data"]["battery"] = *args.battery; }
    if (args.dev_id) { cmd["service_data"]["dev_id"] = *args.dev_id; }
    if (args.gps) { cmd["service_data"]["gps"] = *args.gps; }
    if (args.gps_accuracy) { cmd["service_data"]["gps_accuracy"] = *args.gps_accuracy; }
    if (args.host_name) { cmd["service_data"]["host_name"] = *args.host_name; }
    if (args.location_name) { cmd["service_data"]["location_name"] = *args.location_name; }
    if (args.mac) { cmd["service_data"]["mac"] = *args.mac; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Fan

class Fan : HAEntity
{
  // const EntityType __domain = EntityType::Fan;
  // Decrease speed
  // Decreases the speed of the fan.
  struct decrease_speed_args
  {
    optional<json> percentage_step;
  };
  void decrease_speed(const decrease_speed_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "decrease_speed";
    cmd["target"]["entity_id"] = name;
    if (args.percentage_step) { cmd["service_data"]["percentage_step"] = *args.percentage_step; }

    backend->WSConnSend(cmd);
  }

  // Increase speed
  // Increases the speed of the fan.
  struct increase_speed_args
  {
    optional<json> percentage_step;
  };
  void increase_speed(const increase_speed_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "increase_speed";
    cmd["target"]["entity_id"] = name;
    if (args.percentage_step) { cmd["service_data"]["percentage_step"] = *args.percentage_step; }

    backend->WSConnSend(cmd);
  }

  // Oscillate
  // Controls oscillatation of the fan.
  struct oscillate_args
  {
    optional<json> oscillating;
  };
  void oscillate(const oscillate_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "oscillate";
    cmd["target"]["entity_id"] = name;
    if (args.oscillating) { cmd["service_data"]["oscillating"] = *args.oscillating; }

    backend->WSConnSend(cmd);
  }

  // Set direction
  // Sets the fan rotation direction.
  struct set_direction_args
  {
    optional<json> direction;
  };
  void set_direction(const set_direction_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "set_direction";
    cmd["target"]["entity_id"] = name;
    if (args.direction) { cmd["service_data"]["direction"] = *args.direction; }

    backend->WSConnSend(cmd);
  }

  // Set speed
  // Sets the fan speed.
  struct set_percentage_args
  {
    optional<json> percentage;
  };
  void set_percentage(const set_percentage_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "set_percentage";
    cmd["target"]["entity_id"] = name;
    if (args.percentage) { cmd["service_data"]["percentage"] = *args.percentage; }

    backend->WSConnSend(cmd);
  }

  // Set preset mode
  // Sets preset mode.
  struct set_preset_mode_args
  {
    optional<json> preset_mode;
  };
  void set_preset_mode(const set_preset_mode_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "set_preset_mode";
    cmd["target"]["entity_id"] = name;
    if (args.preset_mode) { cmd["service_data"]["preset_mode"] = *args.preset_mode; }

    backend->WSConnSend(cmd);
  }

  // Toggle
  // Toggles the fan on/off.
  struct toggle_args
  {
  };
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Turns fan off.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Turns fan on.
  struct turn_on_args
  {
    optional<json> percentage;
    optional<json> preset_mode;
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "fan";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;
    if (args.percentage) { cmd["service_data"]["percentage"] = *args.percentage; }
    if (args.preset_mode) { cmd["service_data"]["preset_mode"] = *args.preset_mode; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Ffmpeg

class Ffmpeg : HAEntity
{
  // const EntityType __domain = EntityType::Ffmpeg;
  // Restart
  // Sends a restart command to a ffmpeg based sensor.
  struct restart_args
  {
    optional<json> entity_id;
  };
  void restart(const restart_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "ffmpeg";
    cmd["service"] = "restart";
    cmd["target"]["entity_id"] = name;
    if (args.entity_id) { cmd["service_data"]["entity_id"] = *args.entity_id; }

    backend->WSConnSend(cmd);
  }

  // Start
  // Sends a start command to a ffmpeg based sensor.
  struct start_args
  {
    optional<json> entity_id;
  };
  void start(const start_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "ffmpeg";
    cmd["service"] = "start";
    cmd["target"]["entity_id"] = name;
    if (args.entity_id) { cmd["service_data"]["entity_id"] = *args.entity_id; }

    backend->WSConnSend(cmd);
  }

  // Stop
  // Sends a stop command to a ffmpeg based sensor.
  struct stop_args
  {
    optional<json> entity_id;
  };
  void stop(const stop_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "ffmpeg";
    cmd["service"] = "stop";
    cmd["target"]["entity_id"] = name;
    if (args.entity_id) { cmd["service_data"]["entity_id"] = *args.entity_id; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Frontend

class Frontend : HAEntity
{
  // const EntityType __domain = EntityType::Frontend;
  // Reload themes
  // Reloads themes from the YAML-configuration.
  struct reload_themes_args
  {
  };
  void reload_themes(const reload_themes_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "frontend";
    cmd["service"] = "reload_themes";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Set the default theme
  // Sets the default theme Home Assistant uses. Can be overridden by a user.
  struct set_theme_args
  {
    optional<json> mode;
    optional<json> name;
  };
  void set_theme(const set_theme_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "frontend";
    cmd["service"] = "set_theme";
    cmd["target"]["entity_id"] = name;
    if (args.mode) { cmd["service_data"]["mode"] = *args.mode; }
    if (args.name) { cmd["service_data"]["name"] = *args.name; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Group

class Group : HAEntity
{
  // const EntityType __domain = EntityType::Group;
  // Reload
  // Reloads group configuration, entities, and notify services from YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "group";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Remove
  // Removes a group.
  struct remove_args
  {
    optional<json> object_id;
  };
  void remove(const remove_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "group";
    cmd["service"] = "remove";
    cmd["target"]["entity_id"] = name;
    if (args.object_id) { cmd["service_data"]["object_id"] = *args.object_id; }

    backend->WSConnSend(cmd);
  }

  // Set
  // Creates/Updates a user group.
  struct set_args
  {
    optional<json> add_entities;
    optional<json> all;
    optional<json> entities;
    optional<json> icon;
    optional<json> name;
    optional<json> object_id;
    optional<json> remove_entities;
  };
  void set(const set_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "group";
    cmd["service"] = "set";
    cmd["target"]["entity_id"] = name;
    if (args.add_entities) { cmd["service_data"]["add_entities"] = *args.add_entities; }
    if (args.all) { cmd["service_data"]["all"] = *args.all; }
    if (args.entities) { cmd["service_data"]["entities"] = *args.entities; }
    if (args.icon) { cmd["service_data"]["icon"] = *args.icon; }
    if (args.name) { cmd["service_data"]["name"] = *args.name; }
    if (args.object_id) { cmd["service_data"]["object_id"] = *args.object_id; }
    if (args.remove_entities) { cmd["service_data"]["remove_entities"] = *args.remove_entities; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Homeassistant

class Homeassistant : HAEntity
{
  // const EntityType __domain = EntityType::Homeassistant;
  // Check configuration
  // Checks the Home Assistant YAML-configuration files for errors. Errors will be shown in the Home Assistant logs.
  struct check_config_args
  {
  };
  void check_config(const check_config_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "check_config";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Reload all
  // Reload all YAML configuration that can be reloaded without restarting Home Assistant.
  struct reload_all_args
  {
  };
  void reload_all(const reload_all_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "reload_all";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Reload config entry
  // Reloads the specified config entry.
  struct reload_config_entry_args
  {
    optional<json> entry_id;
  };
  void reload_config_entry(const reload_config_entry_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "reload_config_entry";
    cmd["target"]["entity_id"] = name;
    if (args.entry_id) { cmd["service_data"]["entry_id"] = *args.entry_id; }

    backend->WSConnSend(cmd);
  }

  // Reload core configuration
  // Reloads the core configuration from the YAML-configuration.
  struct reload_core_config_args
  {
  };
  void reload_core_config(const reload_core_config_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "reload_core_config";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Reload custom Jinja2 templates
  // Reloads Jinja2 templates found in the `custom_templates` folder in your config. New values will be applied on the next render of the template.
  struct reload_custom_templates_args
  {
  };
  void reload_custom_templates(const reload_custom_templates_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "reload_custom_templates";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Restart
  // Restarts Home Assistant.
  struct restart_args
  {
  };
  void restart(const restart_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "restart";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Save persistent states
  // Saves the persistent states immediately. Maintains the normal periodic saving interval.
  struct save_persistent_states_args
  {
  };
  void save_persistent_states(const save_persistent_states_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "save_persistent_states";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Set location
  // Updates the Home Assistant location.
  struct set_location_args
  {
    optional<json> elevation;
    optional<json> latitude;
    optional<json> longitude;
  };
  void set_location(const set_location_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "set_location";
    cmd["target"]["entity_id"] = name;
    if (args.elevation) { cmd["service_data"]["elevation"] = *args.elevation; }
    if (args.latitude) { cmd["service_data"]["latitude"] = *args.latitude; }
    if (args.longitude) { cmd["service_data"]["longitude"] = *args.longitude; }

    backend->WSConnSend(cmd);
  }

  // Stop
  // Stops Home Assistant.
  struct stop_args
  {
  };
  void stop(const stop_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "stop";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Generic toggle
  // Generic service to toggle devices on/off under any domain.
  struct toggle_args
  {
  };
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Generic turn off
  // Generic service to turn devices off under any domain.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Generic turn on
  // Generic service to turn devices on under any domain.
  struct turn_on_args
  {
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Update entity
  // Forces one or more entities to update its data.
  struct update_entity_args
  {
  };
  void update_entity(const update_entity_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "homeassistant";
    cmd["service"] = "update_entity";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Humidifier

class Humidifier : HAEntity
{
  // const EntityType __domain = EntityType::Humidifier;
  // Set humidity
  // Sets the target humidity.
  struct set_humidity_args
  {
    optional<json> humidity;
  };
  void set_humidity(const set_humidity_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "humidifier";
    cmd["service"] = "set_humidity";
    cmd["target"]["entity_id"] = name;
    if (args.humidity) { cmd["service_data"]["humidity"] = *args.humidity; }

    backend->WSConnSend(cmd);
  }

  // Set mode
  // Sets the humidifier operation mode.
  struct set_mode_args
  {
    optional<json> mode;
  };
  void set_mode(const set_mode_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "humidifier";
    cmd["service"] = "set_mode";
    cmd["target"]["entity_id"] = name;
    if (args.mode) { cmd["service_data"]["mode"] = *args.mode; }

    backend->WSConnSend(cmd);
  }

  // Toggle
  // Toggles the humidifier on/off.
  struct toggle_args
  {
  };
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "humidifier";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Turns the humidifier off.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "humidifier";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Turns the humidifier on.
  struct turn_on_args
  {
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "humidifier";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Image_processing

class Image_processing : HAEntity
{
  // const EntityType __domain = EntityType::Image_processing;
  // Scan
  // Processes an image immediately.
  struct scan_args
  {
  };
  void scan(const scan_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "image_processing";
    cmd["service"] = "scan";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Input_boolean

class Input_boolean : HAEntity
{
  // const EntityType __domain = EntityType::Input_boolean;
  // Reload
  // Reloads helpers from the YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_boolean";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Toggle
  // Toggles the helper on/off.
  struct toggle_args
  {
  };
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_boolean";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Turns off the helper.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_boolean";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Turns on the helper.
  struct turn_on_args
  {
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_boolean";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Input_button

class Input_button : HAEntity
{
  // const EntityType __domain = EntityType::Input_button;
  // Press
  // Mimics the physical button press on the device.
  struct press_args
  {
  };
  void press(const press_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_button";
    cmd["service"] = "press";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Reload
  // Reloads helpers from the YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_button";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Input_datetime

class Input_datetime : HAEntity
{
  // const EntityType __domain = EntityType::Input_datetime;
  // Reload
  // Reloads helpers from the YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_datetime";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Set
  // Sets the date and/or time.
  struct set_datetime_args
  {
    optional<json> date;
    optional<json> datetime;
    optional<json> time;
    optional<json> timestamp;
  };
  void set_datetime(const set_datetime_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_datetime";
    cmd["service"] = "set_datetime";
    cmd["target"]["entity_id"] = name;
    if (args.date) { cmd["service_data"]["date"] = *args.date; }
    if (args.datetime) { cmd["service_data"]["datetime"] = *args.datetime; }
    if (args.time) { cmd["service_data"]["time"] = *args.time; }
    if (args.timestamp) { cmd["service_data"]["timestamp"] = *args.timestamp; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Input_number

class Input_number : HAEntity
{
  // const EntityType __domain = EntityType::Input_number;
  // Decrement
  // Decrements the current value by 1 step.
  struct decrement_args
  {
  };
  void decrement(const decrement_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_number";
    cmd["service"] = "decrement";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Increment
  // Increments the value by 1 step.
  struct increment_args
  {
  };
  void increment(const increment_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_number";
    cmd["service"] = "increment";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Reload
  // Reloads helpers from the YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_number";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Set
  // Sets the value.
  struct set_value_args
  {
    optional<json> value;
  };
  void set_value(const set_value_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_number";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = name;
    if (args.value) { cmd["service_data"]["value"] = *args.value; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Input_select

class Input_select : HAEntity
{
  // const EntityType __domain = EntityType::Input_select;
  // Reload
  // Reloads helpers from the YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // First
  // Selects the first option.
  struct select_first_args
  {
  };
  void select_first(const select_first_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "select_first";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Last
  // Selects the last option.
  struct select_last_args
  {
  };
  void select_last(const select_last_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "select_last";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Next
  // Select the next option.
  struct select_next_args
  {
    optional<json> cycle;
  };
  void select_next(const select_next_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "select_next";
    cmd["target"]["entity_id"] = name;
    if (args.cycle) { cmd["service_data"]["cycle"] = *args.cycle; }

    backend->WSConnSend(cmd);
  }

  // Select
  // Selects an option.
  struct select_option_args
  {
    optional<json> option;
  };
  void select_option(const select_option_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "select_option";
    cmd["target"]["entity_id"] = name;
    if (args.option) { cmd["service_data"]["option"] = *args.option; }

    backend->WSConnSend(cmd);
  }

  // Previous
  // Selects the previous option.
  struct select_previous_args
  {
    optional<json> cycle;
  };
  void select_previous(const select_previous_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "select_previous";
    cmd["target"]["entity_id"] = name;
    if (args.cycle) { cmd["service_data"]["cycle"] = *args.cycle; }

    backend->WSConnSend(cmd);
  }

  // Set options
  // Sets the options.
  struct set_options_args
  {
    optional<json> options;
  };
  void set_options(const set_options_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_select";
    cmd["service"] = "set_options";
    cmd["target"]["entity_id"] = name;
    if (args.options) { cmd["service_data"]["options"] = *args.options; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Input_text

class Input_text : HAEntity
{
  // const EntityType __domain = EntityType::Input_text;
  // Reload
  // Reloads helpers from the YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_text";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Set
  // Sets the value.
  struct set_value_args
  {
    optional<json> value;
  };
  void set_value(const set_value_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "input_text";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = name;
    if (args.value) { cmd["service_data"]["value"] = *args.value; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Light

class Light : HAEntity
{
  // const EntityType __domain = EntityType::Light;
  // Toggle
  // Toggles one or more lights, from on to off, or, off to on, based on their current state.
  struct toggle_args
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
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "light";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;
    if (args.brightness) { cmd["service_data"]["brightness"] = *args.brightness; }
    if (args.brightness_pct) { cmd["service_data"]["brightness_pct"] = *args.brightness_pct; }
    if (args.color_name) { cmd["service_data"]["color_name"] = *args.color_name; }
    if (args.color_temp) { cmd["service_data"]["color_temp"] = *args.color_temp; }
    if (args.effect) { cmd["service_data"]["effect"] = *args.effect; }
    if (args.flash) { cmd["service_data"]["flash"] = *args.flash; }
    if (args.hs_color) { cmd["service_data"]["hs_color"] = *args.hs_color; }
    if (args.kelvin) { cmd["service_data"]["kelvin"] = *args.kelvin; }
    if (args.profile) { cmd["service_data"]["profile"] = *args.profile; }
    if (args.rgb_color) { cmd["service_data"]["rgb_color"] = *args.rgb_color; }
    if (args.transition) { cmd["service_data"]["transition"] = *args.transition; }
    if (args.white) { cmd["service_data"]["white"] = *args.white; }
    if (args.xy_color) { cmd["service_data"]["xy_color"] = *args.xy_color; }

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Turn off one or more lights.
  struct turn_off_args
  {
    optional<json> flash;
    optional<json> transition;
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "light";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;
    if (args.flash) { cmd["service_data"]["flash"] = *args.flash; }
    if (args.transition) { cmd["service_data"]["transition"] = *args.transition; }

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Turn on one or more lights and adjust properties of the light, even when they are turned on already.
  struct turn_on_args
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
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "light";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;
    if (args.brightness) { cmd["service_data"]["brightness"] = *args.brightness; }
    if (args.brightness_pct) { cmd["service_data"]["brightness_pct"] = *args.brightness_pct; }
    if (args.brightness_step) { cmd["service_data"]["brightness_step"] = *args.brightness_step; }
    if (args.brightness_step_pct) { cmd["service_data"]["brightness_step_pct"] = *args.brightness_step_pct; }
    if (args.color_name) { cmd["service_data"]["color_name"] = *args.color_name; }
    if (args.color_temp) { cmd["service_data"]["color_temp"] = *args.color_temp; }
    if (args.effect) { cmd["service_data"]["effect"] = *args.effect; }
    if (args.flash) { cmd["service_data"]["flash"] = *args.flash; }
    if (args.hs_color) { cmd["service_data"]["hs_color"] = *args.hs_color; }
    if (args.kelvin) { cmd["service_data"]["kelvin"] = *args.kelvin; }
    if (args.profile) { cmd["service_data"]["profile"] = *args.profile; }
    if (args.rgb_color) { cmd["service_data"]["rgb_color"] = *args.rgb_color; }
    if (args.rgbw_color) { cmd["service_data"]["rgbw_color"] = *args.rgbw_color; }
    if (args.rgbww_color) { cmd["service_data"]["rgbww_color"] = *args.rgbww_color; }
    if (args.transition) { cmd["service_data"]["transition"] = *args.transition; }
    if (args.white) { cmd["service_data"]["white"] = *args.white; }
    if (args.xy_color) { cmd["service_data"]["xy_color"] = *args.xy_color; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Lock

class Lock : HAEntity
{
  // const EntityType __domain = EntityType::Lock;
  // Lock
  // Locks a lock.
  struct lock_args
  {
    optional<json> code;
  };
  void lock(const lock_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "lock";
    cmd["service"] = "lock";
    cmd["target"]["entity_id"] = name;
    if (args.code) { cmd["service_data"]["code"] = *args.code; }

    backend->WSConnSend(cmd);
  }

  // Open
  // Opens a lock.
  struct open_args
  {
    optional<json> code;
  };
  void open(const open_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "lock";
    cmd["service"] = "open";
    cmd["target"]["entity_id"] = name;
    if (args.code) { cmd["service_data"]["code"] = *args.code; }

    backend->WSConnSend(cmd);
  }

  // Unlock
  // Unlocks a lock.
  struct unlock_args
  {
    optional<json> code;
  };
  void unlock(const unlock_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "lock";
    cmd["service"] = "unlock";
    cmd["target"]["entity_id"] = name;
    if (args.code) { cmd["service_data"]["code"] = *args.code; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Logbook

class Logbook : HAEntity
{
  // const EntityType __domain = EntityType::Logbook;
  // Log
  // Creates a custom entry in the logbook.
  struct log_args
  {
    optional<json> domain;
    optional<json> entity_id;
    optional<json> message;
    optional<json> name;
  };
  void log(const log_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "logbook";
    cmd["service"] = "log";
    cmd["target"]["entity_id"] = name;
    if (args.domain) { cmd["service_data"]["domain"] = *args.domain; }
    if (args.entity_id) { cmd["service_data"]["entity_id"] = *args.entity_id; }
    if (args.message) { cmd["service_data"]["message"] = *args.message; }
    if (args.name) { cmd["service_data"]["name"] = *args.name; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Logger

class Logger : HAEntity
{
  // const EntityType __domain = EntityType::Logger;
  // Set default level
  // Sets the default log level for integrations.
  struct set_default_level_args
  {
    optional<json> level;
  };
  void set_default_level(const set_default_level_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "logger";
    cmd["service"] = "set_default_level";
    cmd["target"]["entity_id"] = name;
    if (args.level) { cmd["service_data"]["level"] = *args.level; }

    backend->WSConnSend(cmd);
  }

  // Set level
  // Sets the log level for one or more integrations.
  struct set_level_args
  {
  };
  void set_level(const set_level_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "logger";
    cmd["service"] = "set_level";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Media_player

class Media_player : HAEntity
{
  // const EntityType __domain = EntityType::Media_player;
  // Clear playlist
  // Clears the playlist.
  struct clear_playlist_args
  {
  };
  void clear_playlist(const clear_playlist_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "clear_playlist";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Join
  // Groups media players together for synchronous playback. Only works on supported multiroom audio systems.
  struct join_args
  {
    optional<json> group_members;
  };
  void join(const join_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "join";
    cmd["target"]["entity_id"] = name;
    if (args.group_members) { cmd["service_data"]["group_members"] = *args.group_members; }

    backend->WSConnSend(cmd);
  }

  // Next
  // Selects the next track.
  struct media_next_track_args
  {
  };
  void media_next_track(const media_next_track_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_next_track";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Pause
  // Pauses.
  struct media_pause_args
  {
  };
  void media_pause(const media_pause_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_pause";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Play
  // Starts playing.
  struct media_play_args
  {
  };
  void media_play(const media_play_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_play";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Play/Pause
  // Toggles play/pause.
  struct media_play_pause_args
  {
  };
  void media_play_pause(const media_play_pause_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_play_pause";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Previous
  // Selects the previous track.
  struct media_previous_track_args
  {
  };
  void media_previous_track(const media_previous_track_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_previous_track";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Seek
  // Allows you to go to a different part of the media that is currently playing.
  struct media_seek_args
  {
    optional<json> seek_position;
  };
  void media_seek(const media_seek_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_seek";
    cmd["target"]["entity_id"] = name;
    if (args.seek_position) { cmd["service_data"]["seek_position"] = *args.seek_position; }

    backend->WSConnSend(cmd);
  }

  // Stop
  // Stops playing.
  struct media_stop_args
  {
  };
  void media_stop(const media_stop_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "media_stop";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Play media
  // Starts playing specified media.
  struct play_media_args
  {
    optional<json> announce;
    optional<json> enqueue;
    optional<json> media_content_id;
    optional<json> media_content_type;
  };
  void play_media(const play_media_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "play_media";
    cmd["target"]["entity_id"] = name;
    if (args.announce) { cmd["service_data"]["announce"] = *args.announce; }
    if (args.enqueue) { cmd["service_data"]["enqueue"] = *args.enqueue; }
    if (args.media_content_id) { cmd["service_data"]["media_content_id"] = *args.media_content_id; }
    if (args.media_content_type) { cmd["service_data"]["media_content_type"] = *args.media_content_type; }

    backend->WSConnSend(cmd);
  }

  // Repeat
  // Playback mode that plays the media in a loop.
  struct repeat_set_args
  {
    optional<json> repeat;
  };
  void repeat_set(const repeat_set_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "repeat_set";
    cmd["target"]["entity_id"] = name;
    if (args.repeat) { cmd["service_data"]["repeat"] = *args.repeat; }

    backend->WSConnSend(cmd);
  }

  // Select sound mode
  // Selects a specific sound mode.
  struct select_sound_mode_args
  {
    optional<json> sound_mode;
  };
  void select_sound_mode(const select_sound_mode_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "select_sound_mode";
    cmd["target"]["entity_id"] = name;
    if (args.sound_mode) { cmd["service_data"]["sound_mode"] = *args.sound_mode; }

    backend->WSConnSend(cmd);
  }

  // Select source
  // Sends the media player the command to change input source.
  struct select_source_args
  {
    optional<json> source;
  };
  void select_source(const select_source_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "select_source";
    cmd["target"]["entity_id"] = name;
    if (args.source) { cmd["service_data"]["source"] = *args.source; }

    backend->WSConnSend(cmd);
  }

  // Shuffle
  // Playback mode that selects the media in randomized order.
  struct shuffle_set_args
  {
    optional<json> shuffle;
  };
  void shuffle_set(const shuffle_set_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "shuffle_set";
    cmd["target"]["entity_id"] = name;
    if (args.shuffle) { cmd["service_data"]["shuffle"] = *args.shuffle; }

    backend->WSConnSend(cmd);
  }

  // Toggle
  // Toggles a media player on/off.
  struct toggle_args
  {
  };
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Turns off the power of the media player.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Turns on the power of the media player.
  struct turn_on_args
  {
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Unjoin
  // Removes the player from a group. Only works on platforms which support player groups.
  struct unjoin_args
  {
  };
  void unjoin(const unjoin_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "unjoin";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn down volume
  // Turns down the volume.
  struct volume_down_args
  {
  };
  void volume_down(const volume_down_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "volume_down";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Mute/unmute volume
  // Mutes or unmutes the media player.
  struct volume_mute_args
  {
    optional<json> is_volume_muted;
  };
  void volume_mute(const volume_mute_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "volume_mute";
    cmd["target"]["entity_id"] = name;
    if (args.is_volume_muted) { cmd["service_data"]["is_volume_muted"] = *args.is_volume_muted; }

    backend->WSConnSend(cmd);
  }

  // Set volume
  // Sets the volume level.
  struct volume_set_args
  {
    optional<json> volume_level;
  };
  void volume_set(const volume_set_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "volume_set";
    cmd["target"]["entity_id"] = name;
    if (args.volume_level) { cmd["service_data"]["volume_level"] = *args.volume_level; }

    backend->WSConnSend(cmd);
  }

  // Turn up volume
  // Turns up the volume.
  struct volume_up_args
  {
  };
  void volume_up(const volume_up_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "media_player";
    cmd["service"] = "volume_up";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Notify

class Notify : HAEntity
{
  // const EntityType __domain = EntityType::Notify;
  // Send a notification via demo_test_target_name
  // Sends a notification message using the demo_test_target_name integration.
  struct demo_test_target_name_args
  {
    optional<json> data;
    optional<json> message;
    optional<json> target;
    optional<json> title;
  };
  void demo_test_target_name(const demo_test_target_name_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "notify";
    cmd["service"] = "demo_test_target_name";
    cmd["target"]["entity_id"] = name;
    if (args.data) { cmd["service_data"]["data"] = *args.data; }
    if (args.message) { cmd["service_data"]["message"] = *args.message; }
    if (args.target) { cmd["service_data"]["target"] = *args.target; }
    if (args.title) { cmd["service_data"]["title"] = *args.title; }

    backend->WSConnSend(cmd);
  }

  // Send a notification with notify
  // Sends a notification message using the notify service.
  struct notify_args
  {
    optional<json> data;
    optional<json> message;
    optional<json> target;
    optional<json> title;
  };
  void notify(const notify_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "notify";
    cmd["service"] = "notify";
    cmd["target"]["entity_id"] = name;
    if (args.data) { cmd["service_data"]["data"] = *args.data; }
    if (args.message) { cmd["service_data"]["message"] = *args.message; }
    if (args.target) { cmd["service_data"]["target"] = *args.target; }
    if (args.title) { cmd["service_data"]["title"] = *args.title; }

    backend->WSConnSend(cmd);
  }

  // Send a persistent notification
  // Sends a notification that is visible in the **Notifications** panel.
  struct persistent_notification_args
  {
    optional<json> data;
    optional<json> message;
    optional<json> title;
  };
  void persistent_notification(const persistent_notification_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "notify";
    cmd["service"] = "persistent_notification";
    cmd["target"]["entity_id"] = name;
    if (args.data) { cmd["service_data"]["data"] = *args.data; }
    if (args.message) { cmd["service_data"]["message"] = *args.message; }
    if (args.title) { cmd["service_data"]["title"] = *args.title; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Number

class Number : HAEntity
{
  // const EntityType __domain = EntityType::Number;
  // Set
  // Sets the value of a number.
  struct set_value_args
  {
    optional<json> value;
  };
  void set_value(const set_value_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "number";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = name;
    if (args.value) { cmd["service_data"]["value"] = *args.value; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Persistent_notification

class Persistent_notification : HAEntity
{
  // const EntityType __domain = EntityType::Persistent_notification;
  // Create
  // Shows a notification on the **Notifications** panel.
  struct create_args
  {
    optional<json> message;
    optional<json> notification_id;
    optional<json> title;
  };
  void create(const create_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "persistent_notification";
    cmd["service"] = "create";
    cmd["target"]["entity_id"] = name;
    if (args.message) { cmd["service_data"]["message"] = *args.message; }
    if (args.notification_id) { cmd["service_data"]["notification_id"] = *args.notification_id; }
    if (args.title) { cmd["service_data"]["title"] = *args.title; }

    backend->WSConnSend(cmd);
  }

  // Dismiss
  // Removes a notification from the **Notifications** panel.
  struct dismiss_args
  {
    optional<json> notification_id;
  };
  void dismiss(const dismiss_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "persistent_notification";
    cmd["service"] = "dismiss";
    cmd["target"]["entity_id"] = name;
    if (args.notification_id) { cmd["service_data"]["notification_id"] = *args.notification_id; }

    backend->WSConnSend(cmd);
  }

  // Dismiss all
  // Removes all notifications from the **Notifications** panel.
  struct dismiss_all_args
  {
  };
  void dismiss_all(const dismiss_all_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "persistent_notification";
    cmd["service"] = "dismiss_all";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Person

class Person : HAEntity
{
  // const EntityType __domain = EntityType::Person;
  // Reload
  // Reloads persons from the YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "person";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Recorder

class Recorder : HAEntity
{
  // const EntityType __domain = EntityType::Recorder;
  // Disable
  // Stops the recording of events and state changes.
  struct disable_args
  {
  };
  void disable(const disable_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "recorder";
    cmd["service"] = "disable";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Enable
  // Starts the recording of events and state changes.
  struct enable_args
  {
  };
  void enable(const enable_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "recorder";
    cmd["service"] = "enable";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Purge
  // Starts purge task - to clean up old data from your database.
  struct purge_args
  {
    optional<json> apply_filter;
    optional<json> keep_days;
    optional<json> repack;
  };
  void purge(const purge_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "recorder";
    cmd["service"] = "purge";
    cmd["target"]["entity_id"] = name;
    if (args.apply_filter) { cmd["service_data"]["apply_filter"] = *args.apply_filter; }
    if (args.keep_days) { cmd["service_data"]["keep_days"] = *args.keep_days; }
    if (args.repack) { cmd["service_data"]["repack"] = *args.repack; }

    backend->WSConnSend(cmd);
  }

  // Purge entities
  // Starts a purge task to remove the data related to specific entities from your database.
  struct purge_entities_args
  {
    optional<json> domains;
    optional<json> entity_globs;
    optional<json> keep_days;
  };
  void purge_entities(const purge_entities_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "recorder";
    cmd["service"] = "purge_entities";
    cmd["target"]["entity_id"] = name;
    if (args.domains) { cmd["service_data"]["domains"] = *args.domains; }
    if (args.entity_globs) { cmd["service_data"]["entity_globs"] = *args.entity_globs; }
    if (args.keep_days) { cmd["service_data"]["keep_days"] = *args.keep_days; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Scene

class Scene : HAEntity
{
  // const EntityType __domain = EntityType::Scene;
  // Apply
  // Activates a scene with configuration.
  struct apply_args
  {
    optional<json> entities;
    optional<json> transition;
  };
  void apply(const apply_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "scene";
    cmd["service"] = "apply";
    cmd["target"]["entity_id"] = name;
    if (args.entities) { cmd["service_data"]["entities"] = *args.entities; }
    if (args.transition) { cmd["service_data"]["transition"] = *args.transition; }

    backend->WSConnSend(cmd);
  }

  // Create
  // Creates a new scene.
  struct create_args
  {
    optional<json> entities;
    optional<json> scene_id;
    optional<json> snapshot_entities;
  };
  void create(const create_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "scene";
    cmd["service"] = "create";
    cmd["target"]["entity_id"] = name;
    if (args.entities) { cmd["service_data"]["entities"] = *args.entities; }
    if (args.scene_id) { cmd["service_data"]["scene_id"] = *args.scene_id; }
    if (args.snapshot_entities) { cmd["service_data"]["snapshot_entities"] = *args.snapshot_entities; }

    backend->WSConnSend(cmd);
  }

  // Delete
  // Deletes a dynamically created scene.
  struct delete_args
  {
  };
  void _delete(const delete_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "scene";
    cmd["service"] = "delete";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Reload
  // Reloads the scenes from the YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "scene";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Activate
  // Activates a scene.
  struct turn_on_args
  {
    optional<json> transition;
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "scene";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;
    if (args.transition) { cmd["service_data"]["transition"] = *args.transition; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Schedule

class Schedule : HAEntity
{
  // const EntityType __domain = EntityType::Schedule;
  // Reload
  // Reloads schedules from the YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "schedule";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Script

class Script : HAEntity
{
  // const EntityType __domain = EntityType::Script;
  // Reload
  // Reloads all the available scripts.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "script";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Toggle
  // Toggle a script. Starts it, if isn't running, stops it otherwise.
  struct toggle_args
  {
  };
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "script";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Stops a running script.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "script";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Runs the sequence of actions defined in a script.
  struct turn_on_args
  {
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "script";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Select

class Select : HAEntity
{
  // const EntityType __domain = EntityType::Select;
  // First
  // Selects the first option.
  struct select_first_args
  {
  };
  void select_first(const select_first_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "select";
    cmd["service"] = "select_first";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Last
  // Selects the last option.
  struct select_last_args
  {
  };
  void select_last(const select_last_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "select";
    cmd["service"] = "select_last";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Next
  // Selects the next option.
  struct select_next_args
  {
    optional<json> cycle;
  };
  void select_next(const select_next_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "select";
    cmd["service"] = "select_next";
    cmd["target"]["entity_id"] = name;
    if (args.cycle) { cmd["service_data"]["cycle"] = *args.cycle; }

    backend->WSConnSend(cmd);
  }

  // Select
  // Selects an option.
  struct select_option_args
  {
    optional<json> option;
  };
  void select_option(const select_option_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "select";
    cmd["service"] = "select_option";
    cmd["target"]["entity_id"] = name;
    if (args.option) { cmd["service_data"]["option"] = *args.option; }

    backend->WSConnSend(cmd);
  }

  // Previous
  // Selects the previous option.
  struct select_previous_args
  {
    optional<json> cycle;
  };
  void select_previous(const select_previous_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "select";
    cmd["service"] = "select_previous";
    cmd["target"]["entity_id"] = name;
    if (args.cycle) { cmd["service_data"]["cycle"] = *args.cycle; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Shopping_list

class Shopping_list : HAEntity
{
  // const EntityType __domain = EntityType::Shopping_list;
  // Add item
  // Adds an item to the shopping list.
  struct add_item_args
  {
    optional<json> name;
  };
  void add_item(const add_item_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "add_item";
    cmd["target"]["entity_id"] = name;
    if (args.name) { cmd["service_data"]["name"] = *args.name; }

    backend->WSConnSend(cmd);
  }

  // Clear completed items
  // Clears completed items from the shopping list.
  struct clear_completed_items_args
  {
  };
  void clear_completed_items(const clear_completed_items_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "clear_completed_items";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Complete all
  // Marks all items as completed in the shopping list (without removing them from the list).
  struct complete_all_args
  {
  };
  void complete_all(const complete_all_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "complete_all";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Complete item
  // Marks the first item with matching name as completed in the shopping list.
  struct complete_item_args
  {
    optional<json> name;
  };
  void complete_item(const complete_item_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "complete_item";
    cmd["target"]["entity_id"] = name;
    if (args.name) { cmd["service_data"]["name"] = *args.name; }

    backend->WSConnSend(cmd);
  }

  // Incomplete all
  // Marks all items as incomplete in the shopping list.
  struct incomplete_all_args
  {
  };
  void incomplete_all(const incomplete_all_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "incomplete_all";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Incomplete item
  // Marks the first item with matching name as incomplete in the shopping list.
  struct incomplete_item_args
  {
    optional<json> name;
  };
  void incomplete_item(const incomplete_item_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "incomplete_item";
    cmd["target"]["entity_id"] = name;
    if (args.name) { cmd["service_data"]["name"] = *args.name; }

    backend->WSConnSend(cmd);
  }

  // Remove item
  // Removes the first item with matching name from the shopping list.
  struct remove_item_args
  {
    optional<json> name;
  };
  void remove_item(const remove_item_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "remove_item";
    cmd["target"]["entity_id"] = name;
    if (args.name) { cmd["service_data"]["name"] = *args.name; }

    backend->WSConnSend(cmd);
  }

  // Sort all items
  // Sorts all items by name in the shopping list.
  struct sort_args
  {
    optional<json> reverse;
  };
  void sort(const sort_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "shopping_list";
    cmd["service"] = "sort";
    cmd["target"]["entity_id"] = name;
    if (args.reverse) { cmd["service_data"]["reverse"] = *args.reverse; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Siren

class Siren : HAEntity
{
  // const EntityType __domain = EntityType::Siren;
  // Toggle
  // Toggles the siren on/off.
  struct toggle_args
  {
  };
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "siren";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Turns the siren off.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "siren";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Turns the siren on.
  struct turn_on_args
  {
    optional<json> duration;
    optional<json> tone;
    optional<json> volume_level;
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "siren";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;
    if (args.duration) { cmd["service_data"]["duration"] = *args.duration; }
    if (args.tone) { cmd["service_data"]["tone"] = *args.tone; }
    if (args.volume_level) { cmd["service_data"]["volume_level"] = *args.volume_level; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Switch

class Switch : HAEntity
{
  // const EntityType __domain = EntityType::Switch;
  // Toggle
  // Toggles a switch on/off.
  struct toggle_args
  {
  };
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "switch";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Turns a switch off.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "switch";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Turns a switch on.
  struct turn_on_args
  {
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "switch";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR System_log

class System_log : HAEntity
{
  // const EntityType __domain = EntityType::System_log;
  // Clear all
  // Clears all log entries.
  struct clear_args
  {
  };
  void clear(const clear_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "system_log";
    cmd["service"] = "clear";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Write
  // Write log entry.
  struct write_args
  {
    optional<json> level;
    optional<json> logger;
    optional<json> message;
  };
  void write(const write_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "system_log";
    cmd["service"] = "write";
    cmd["target"]["entity_id"] = name;
    if (args.level) { cmd["service_data"]["level"] = *args.level; }
    if (args.logger) { cmd["service_data"]["logger"] = *args.logger; }
    if (args.message) { cmd["service_data"]["message"] = *args.message; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Text

class Text : HAEntity
{
  // const EntityType __domain = EntityType::Text;
  // Set value
  // Sets the value.
  struct set_value_args
  {
    optional<json> value;
  };
  void set_value(const set_value_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "text";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = name;
    if (args.value) { cmd["service_data"]["value"] = *args.value; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Time

class Time : HAEntity
{
  // const EntityType __domain = EntityType::Time;
  // Set Time
  // Sets the time.
  struct set_value_args
  {
    optional<json> time;
  };
  void set_value(const set_value_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "time";
    cmd["service"] = "set_value";
    cmd["target"]["entity_id"] = name;
    if (args.time) { cmd["service_data"]["time"] = *args.time; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Timer

class Timer : HAEntity
{
  // const EntityType __domain = EntityType::Timer;
  // Cancel
  // Cancels a timer.
  struct cancel_args
  {
  };
  void cancel(const cancel_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "cancel";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Change
  // Changes a timer.
  struct change_args
  {
    optional<json> duration;
  };
  void change(const change_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "change";
    cmd["target"]["entity_id"] = name;
    if (args.duration) { cmd["service_data"]["duration"] = *args.duration; }

    backend->WSConnSend(cmd);
  }

  // Finish
  // Finishes a timer.
  struct finish_args
  {
  };
  void finish(const finish_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "finish";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Pause
  // Pauses a timer.
  struct pause_args
  {
  };
  void pause(const pause_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "pause";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Reload
  // Reloads timers from the YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Start
  // Starts a timer.
  struct start_args
  {
    optional<json> duration;
  };
  void start(const start_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "timer";
    cmd["service"] = "start";
    cmd["target"]["entity_id"] = name;
    if (args.duration) { cmd["service_data"]["duration"] = *args.duration; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Todo

class Todo : HAEntity
{
  // const EntityType __domain = EntityType::Todo;
  // Add to-do list item
  // Add a new to-do list item.
  struct add_item_args
  {
    optional<json> description;
    optional<json> due_date;
    optional<json> due_datetime;
    optional<json> item;
  };
  void add_item(const add_item_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "todo";
    cmd["service"] = "add_item";
    cmd["target"]["entity_id"] = name;
    if (args.description) { cmd["service_data"]["description"] = *args.description; }
    if (args.due_date) { cmd["service_data"]["due_date"] = *args.due_date; }
    if (args.due_datetime) { cmd["service_data"]["due_datetime"] = *args.due_datetime; }
    if (args.item) { cmd["service_data"]["item"] = *args.item; }

    backend->WSConnSend(cmd);
  }

  // Get to-do list items
  // Get items on a to-do list.
  struct get_items_args
  {
    optional<json> status;
  };
  void get_items(const get_items_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "todo";
    cmd["service"] = "get_items";
    cmd["target"]["entity_id"] = name;
    if (args.status) { cmd["service_data"]["status"] = *args.status; }

    backend->WSConnSend(cmd);
  }

  // Remove all completed to-do list items
  // Remove all to-do list items that have been completed.
  struct remove_completed_items_args
  {
  };
  void remove_completed_items(const remove_completed_items_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "todo";
    cmd["service"] = "remove_completed_items";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Remove a to-do list item
  // Remove an existing to-do list item by its name.
  struct remove_item_args
  {
    optional<json> item;
  };
  void remove_item(const remove_item_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "todo";
    cmd["service"] = "remove_item";
    cmd["target"]["entity_id"] = name;
    if (args.item) { cmd["service_data"]["item"] = *args.item; }

    backend->WSConnSend(cmd);
  }

  // Update to-do list item
  // Update an existing to-do list item based on its name.
  struct update_item_args
  {
    optional<json> description;
    optional<json> due_date;
    optional<json> due_datetime;
    optional<json> item;
    optional<json> rename;
    optional<json> status;
  };
  void update_item(const update_item_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "todo";
    cmd["service"] = "update_item";
    cmd["target"]["entity_id"] = name;
    if (args.description) { cmd["service_data"]["description"] = *args.description; }
    if (args.due_date) { cmd["service_data"]["due_date"] = *args.due_date; }
    if (args.due_datetime) { cmd["service_data"]["due_datetime"] = *args.due_datetime; }
    if (args.item) { cmd["service_data"]["item"] = *args.item; }
    if (args.rename) { cmd["service_data"]["rename"] = *args.rename; }
    if (args.status) { cmd["service_data"]["status"] = *args.status; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Tts

class Tts : HAEntity
{
  // const EntityType __domain = EntityType::Tts;
  // Clear TTS cache
  // Removes all cached text-to-speech files and purges the memory.
  struct clear_cache_args
  {
  };
  void clear_cache(const clear_cache_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "tts";
    cmd["service"] = "clear_cache";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Say a TTS message with demo
  // Say something using text-to-speech on a media player with demo.
  struct demo_say_args
  {
    optional<json> cache;
    optional<json> entity_id;
    optional<json> language;
    optional<json> message;
    optional<json> options;
  };
  void demo_say(const demo_say_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "tts";
    cmd["service"] = "demo_say";
    cmd["target"]["entity_id"] = name;
    if (args.cache) { cmd["service_data"]["cache"] = *args.cache; }
    if (args.entity_id) { cmd["service_data"]["entity_id"] = *args.entity_id; }
    if (args.language) { cmd["service_data"]["language"] = *args.language; }
    if (args.message) { cmd["service_data"]["message"] = *args.message; }
    if (args.options) { cmd["service_data"]["options"] = *args.options; }

    backend->WSConnSend(cmd);
  }

  // Speak
  // Speaks something using text-to-speech on a media player.
  struct speak_args
  {
    optional<json> cache;
    optional<json> language;
    optional<json> media_player_entity_id;
    optional<json> message;
    optional<json> options;
  };
  void speak(const speak_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "tts";
    cmd["service"] = "speak";
    cmd["target"]["entity_id"] = name;
    if (args.cache) { cmd["service_data"]["cache"] = *args.cache; }
    if (args.language) { cmd["service_data"]["language"] = *args.language; }
    if (args.media_player_entity_id) { cmd["service_data"]["media_player_entity_id"] = *args.media_player_entity_id; }
    if (args.message) { cmd["service_data"]["message"] = *args.message; }
    if (args.options) { cmd["service_data"]["options"] = *args.options; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Update

class Update : HAEntity
{
  // const EntityType __domain = EntityType::Update;
  // Clear skipped update
  // Removes the skipped version marker from an update.
  struct clear_skipped_args
  {
  };
  void clear_skipped(const clear_skipped_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "update";
    cmd["service"] = "clear_skipped";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Install update
  // Installs an update for this device or service.
  struct install_args
  {
    optional<json> backup;
    optional<json> version;
  };
  void install(const install_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "update";
    cmd["service"] = "install";
    cmd["target"]["entity_id"] = name;
    if (args.backup) { cmd["service_data"]["backup"] = *args.backup; }
    if (args.version) { cmd["service_data"]["version"] = *args.version; }

    backend->WSConnSend(cmd);
  }

  // Skip update
  // Marks currently available update as skipped.
  struct skip_args
  {
  };
  void skip(const skip_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "update";
    cmd["service"] = "skip";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Vacuum

class Vacuum : HAEntity
{
  // const EntityType __domain = EntityType::Vacuum;
  // Clean spot
  // Tells the vacuum cleaner to do a spot clean-up.
  struct clean_spot_args
  {
  };
  void clean_spot(const clean_spot_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "clean_spot";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Locate
  // Locates the vacuum cleaner robot.
  struct locate_args
  {
  };
  void locate(const locate_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "locate";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Pause
  // Pauses the cleaning task.
  struct pause_args
  {
  };
  void pause(const pause_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "pause";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Return to dock
  // Tells the vacuum cleaner to return to its dock.
  struct return_to_base_args
  {
  };
  void return_to_base(const return_to_base_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "return_to_base";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Send command
  // Sends a command to the vacuum cleaner.
  struct send_command_args
  {
    optional<json> command;
    optional<json> params;
  };
  void send_command(const send_command_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "send_command";
    cmd["target"]["entity_id"] = name;
    if (args.command) { cmd["service_data"]["command"] = *args.command; }
    if (args.params) { cmd["service_data"]["params"] = *args.params; }

    backend->WSConnSend(cmd);
  }

  // Set fan speed
  // Sets the fan speed of the vacuum cleaner.
  struct set_fan_speed_args
  {
    optional<json> fan_speed;
  };
  void set_fan_speed(const set_fan_speed_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "set_fan_speed";
    cmd["target"]["entity_id"] = name;
    if (args.fan_speed) { cmd["service_data"]["fan_speed"] = *args.fan_speed; }

    backend->WSConnSend(cmd);
  }

  // Start
  // Starts or resumes the cleaning task.
  struct start_args
  {
  };
  void start(const start_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "start";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Start/pause
  // Starts, pauses, or resumes the cleaning task.
  struct start_pause_args
  {
  };
  void start_pause(const start_pause_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "start_pause";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Stop
  // Stops the current cleaning task.
  struct stop_args
  {
  };
  void stop(const stop_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "stop";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Toggle
  // Toggles the vacuum cleaner on/off.
  struct toggle_args
  {
  };
  void toggle(const toggle_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "toggle";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Stops the current cleaning task and returns to its dock.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Starts a new cleaning task.
  struct turn_on_args
  {
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "vacuum";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Water_heater

class Water_heater : HAEntity
{
  // const EntityType __domain = EntityType::Water_heater;
  // Set away mode
  // Turns away mode on/off.
  struct set_away_mode_args
  {
    optional<json> away_mode;
  };
  void set_away_mode(const set_away_mode_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "water_heater";
    cmd["service"] = "set_away_mode";
    cmd["target"]["entity_id"] = name;
    if (args.away_mode) { cmd["service_data"]["away_mode"] = *args.away_mode; }

    backend->WSConnSend(cmd);
  }

  // Set operation mode
  // Sets the operation mode.
  struct set_operation_mode_args
  {
    optional<json> operation_mode;
  };
  void set_operation_mode(const set_operation_mode_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "water_heater";
    cmd["service"] = "set_operation_mode";
    cmd["target"]["entity_id"] = name;
    if (args.operation_mode) { cmd["service_data"]["operation_mode"] = *args.operation_mode; }

    backend->WSConnSend(cmd);
  }

  // Set temperature
  // Sets the target temperature.
  struct set_temperature_args
  {
    optional<json> operation_mode;
    optional<json> temperature;
  };
  void set_temperature(const set_temperature_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "water_heater";
    cmd["service"] = "set_temperature";
    cmd["target"]["entity_id"] = name;
    if (args.operation_mode) { cmd["service_data"]["operation_mode"] = *args.operation_mode; }
    if (args.temperature) { cmd["service_data"]["temperature"] = *args.temperature; }

    backend->WSConnSend(cmd);
  }

  // Turn off
  // Turns water heater off.
  struct turn_off_args
  {
  };
  void turn_off(const turn_off_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "water_heater";
    cmd["service"] = "turn_off";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }

  // Turn on
  // Turns water heater on.
  struct turn_on_args
  {
  };
  void turn_on(const turn_on_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "water_heater";
    cmd["service"] = "turn_on";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Weather

class Weather : HAEntity
{
  // const EntityType __domain = EntityType::Weather;
  // Get forecast
  // Get weather forecast.
  struct get_forecast_args
  {
    optional<json> type;
  };
  void get_forecast(const get_forecast_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "weather";
    cmd["service"] = "get_forecast";
    cmd["target"]["entity_id"] = name;
    if (args.type) { cmd["service_data"]["type"] = *args.type; }

    backend->WSConnSend(cmd);
  }

  // Get forecasts
  // Get weather forecasts.
  struct get_forecasts_args
  {
    optional<json> type;
  };
  void get_forecasts(const get_forecasts_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "weather";
    cmd["service"] = "get_forecasts";
    cmd["target"]["entity_id"] = name;
    if (args.type) { cmd["service_data"]["type"] = *args.type; }

    backend->WSConnSend(cmd);
  }
};

// START HEADER FOR Zone

class Zone : HAEntity
{
  // const EntityType __domain = EntityType::Zone;
  // Reload
  // Reloads zones from the YAML-configuration.
  struct reload_args
  {
  };
  void reload(const reload_args& args) {
    json cmd;

    cmd["type"] = "call_service";
    cmd["domain"] = "zone";
    cmd["service"] = "reload";
    cmd["target"]["entity_id"] = name;

    backend->WSConnSend(cmd);
  }
};

}
