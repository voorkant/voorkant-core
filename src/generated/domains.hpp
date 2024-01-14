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
  class alarm_arm_away_args
  {
    optional<json> code;
  };
  void alarm_arm_away(const alarm_arm_away_args& args);

  // Arm with custom bypass
  // Arms the alarm while allowing to bypass a custom area.
  class alarm_arm_custom_bypass_args
  {
    optional<json> code;
  };
  void alarm_arm_custom_bypass(const alarm_arm_custom_bypass_args& args);

  // Arm home
  // Sets the alarm to: _armed, but someone is home_.
  class alarm_arm_home_args
  {
    optional<json> code;
  };
  void alarm_arm_home(const alarm_arm_home_args& args);

  // Arm night
  // Sets the alarm to: _armed for the night_.
  class alarm_arm_night_args
  {
    optional<json> code;
  };
  void alarm_arm_night(const alarm_arm_night_args& args);

  // Arm vacation
  // Sets the alarm to: _armed for vacation_.
  class alarm_arm_vacation_args
  {
    optional<json> code;
  };
  void alarm_arm_vacation(const alarm_arm_vacation_args& args);

  // Disarm
  // Disarms the alarm.
  class alarm_disarm_args
  {
    optional<json> code;
  };
  void alarm_disarm(const alarm_disarm_args& args);

  // Trigger
  // Enables an external alarm trigger.
  class alarm_trigger_args
  {
    optional<json> code;
  };
  void alarm_trigger(const alarm_trigger_args& args);
};

// START HEADER FOR Automation

class Automation : HAEntity
{
  // const EntityType __domain = EntityType::Automation;
  // Reload
  // Reloads the automation configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);

  // Toggle
  // Toggles (enable / disable) an automation.
  class toggle_args
  {
  };
  void toggle(const toggle_args& args);

  // Trigger
  // Triggers the actions of an automation.
  class trigger_args
  {
    optional<json> skip_condition;
  };
  void trigger(const trigger_args& args);

  // Turn off
  // Disables an automation.
  class turn_off_args
  {
    optional<json> stop_actions;
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Enables an automation.
  class turn_on_args
  {
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Backup

class Backup : HAEntity
{
  // const EntityType __domain = EntityType::Backup;
  // Create backup
  // Creates a new backup.
  class create_args
  {
  };
  void create(const create_args& args);
};

// START HEADER FOR Button

class Button : HAEntity
{
  // const EntityType __domain = EntityType::Button;
  // Press
  // Press the button entity.
  class press_args
  {
  };
  void press(const press_args& args);
};

// START HEADER FOR Calendar

class Calendar : HAEntity
{
  // const EntityType __domain = EntityType::Calendar;
  // Create event
  // Adds a new calendar event.
  class create_event_args
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
  void create_event(const create_event_args& args);

  // Get events
  // Get events on a calendar within a time range.
  class get_events_args
  {
    optional<json> duration;
    optional<json> end_date_time;
    optional<json> start_date_time;
  };
  void get_events(const get_events_args& args);

  // List event
  // Lists events on a calendar within a time range.
  class list_events_args
  {
    optional<json> duration;
    optional<json> end_date_time;
    optional<json> start_date_time;
  };
  void list_events(const list_events_args& args);
};

// START HEADER FOR Camera

class Camera : HAEntity
{
  // const EntityType __domain = EntityType::Camera;
  // Disable motion detection
  // Disables the motion detection.
  class disable_motion_detection_args
  {
  };
  void disable_motion_detection(const disable_motion_detection_args& args);

  // Enable motion detection
  // Enables the motion detection.
  class enable_motion_detection_args
  {
  };
  void enable_motion_detection(const enable_motion_detection_args& args);

  // Play stream
  // Plays the camera stream on a supported media player.
  class play_stream_args
  {
    optional<json> format;
    optional<json> media_player;
  };
  void play_stream(const play_stream_args& args);

  // Record
  // Creates a recording of a live camera feed.
  class record_args
  {
    optional<json> duration;
    optional<json> filename;
    optional<json> lookback;
  };
  void record(const record_args& args);

  // Take snapshot
  // Takes a snapshot from a camera.
  class snapshot_args
  {
    optional<json> filename;
  };
  void snapshot(const snapshot_args& args);

  // Turn off
  // Turns off the camera.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Turns on the camera.
  class turn_on_args
  {
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Climate

class Climate : HAEntity
{
  // const EntityType __domain = EntityType::Climate;
  // Turn on/off auxiliary heater
  // Turns auxiliary heater on/off.
  class set_aux_heat_args
  {
    optional<json> aux_heat;
  };
  void set_aux_heat(const set_aux_heat_args& args);

  // Set fan mode
  // Sets fan operation mode.
  class set_fan_mode_args
  {
    optional<json> fan_mode;
  };
  void set_fan_mode(const set_fan_mode_args& args);

  // Set target humidity
  // Sets target humidity.
  class set_humidity_args
  {
    optional<json> humidity;
  };
  void set_humidity(const set_humidity_args& args);

  // Set HVAC mode
  // Sets HVAC operation mode.
  class set_hvac_mode_args
  {
    optional<json> hvac_mode;
  };
  void set_hvac_mode(const set_hvac_mode_args& args);

  // Set preset mode
  // Sets preset mode.
  class set_preset_mode_args
  {
    optional<json> preset_mode;
  };
  void set_preset_mode(const set_preset_mode_args& args);

  // Set swing mode
  // Sets swing operation mode.
  class set_swing_mode_args
  {
    optional<json> swing_mode;
  };
  void set_swing_mode(const set_swing_mode_args& args);

  // Set target temperature
  // Sets target temperature.
  class set_temperature_args
  {
    optional<json> hvac_mode;
    optional<json> target_temp_high;
    optional<json> target_temp_low;
    optional<json> temperature;
  };
  void set_temperature(const set_temperature_args& args);

  // Turn off
  // Turns climate device off.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Turns climate device on.
  class turn_on_args
  {
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Cloud

class Cloud : HAEntity
{
  // const EntityType __domain = EntityType::Cloud;
  // Remote connect
  // Makes the instance UI accessible from outside of the local network by using Home Assistant Cloud.
  class remote_connect_args
  {
  };
  void remote_connect(const remote_connect_args& args);

  // Remote disconnect
  // Disconnects the Home Assistant UI from the Home Assistant Cloud. You will no longer be able to access your Home Assistant instance from outside your local network.
  class remote_disconnect_args
  {
  };
  void remote_disconnect(const remote_disconnect_args& args);
};

// START HEADER FOR Conversation

class Conversation : HAEntity
{
  // const EntityType __domain = EntityType::Conversation;
  // Process
  // Launches a conversation from a transcribed text.
  class process_args
  {
    optional<json> agent_id;
    optional<json> language;
    optional<json> text;
  };
  void process(const process_args& args);

  // Reload
  // Reloads the intent configuration.
  class reload_args
  {
    optional<json> agent_id;
    optional<json> language;
  };
  void reload(const reload_args& args);
};

// START HEADER FOR Counter

class Counter : HAEntity
{
  // const EntityType __domain = EntityType::Counter;
  // Decrement
  // Decrements a counter.
  class decrement_args
  {
  };
  void decrement(const decrement_args& args);

  // Increment
  // Increments a counter.
  class increment_args
  {
  };
  void increment(const increment_args& args);

  // Reset
  // Resets a counter.
  class reset_args
  {
  };
  void reset(const reset_args& args);

  // Set
  // Sets the counter value.
  class set_value_args
  {
    optional<json> value;
  };
  void set_value(const set_value_args& args);
};

// START HEADER FOR Cover

class Cover : HAEntity
{
  // const EntityType __domain = EntityType::Cover;
  // Close
  // Closes a cover.
  class close_cover_args
  {
  };
  void close_cover(const close_cover_args& args);

  // Close tilt
  // Tilts a cover to close.
  class close_cover_tilt_args
  {
  };
  void close_cover_tilt(const close_cover_tilt_args& args);

  // Open
  // Opens a cover.
  class open_cover_args
  {
  };
  void open_cover(const open_cover_args& args);

  // Open tilt
  // Tilts a cover open.
  class open_cover_tilt_args
  {
  };
  void open_cover_tilt(const open_cover_tilt_args& args);

  // Set position
  // Moves a cover to a specific position.
  class set_cover_position_args
  {
    optional<json> position;
  };
  void set_cover_position(const set_cover_position_args& args);

  // Set tilt position
  // Moves a cover tilt to a specific position.
  class set_cover_tilt_position_args
  {
    optional<json> tilt_position;
  };
  void set_cover_tilt_position(const set_cover_tilt_position_args& args);

  // Stop
  // Stops the cover movement.
  class stop_cover_args
  {
  };
  void stop_cover(const stop_cover_args& args);

  // Stop tilt
  // Stops a tilting cover movement.
  class stop_cover_tilt_args
  {
  };
  void stop_cover_tilt(const stop_cover_tilt_args& args);

  // Toggle
  // Toggles a cover open/closed.
  class toggle_args
  {
  };
  void toggle(const toggle_args& args);

  // Toggle tilt
  // Toggles a cover tilt open/closed.
  class toggle_cover_tilt_args
  {
  };
  void toggle_cover_tilt(const toggle_cover_tilt_args& args);
};

// START HEADER FOR Date

class Date : HAEntity
{
  // const EntityType __domain = EntityType::Date;
  // Set date
  // Sets the date.
  class set_value_args
  {
    optional<json> date;
  };
  void set_value(const set_value_args& args);
};

// START HEADER FOR Datetime

class Datetime : HAEntity
{
  // const EntityType __domain = EntityType::Datetime;
  // Set date/time
  // Sets the date/time for a datetime entity.
  class set_value_args
  {
    optional<json> datetime;
  };
  void set_value(const set_value_args& args);
};

// START HEADER FOR Demo

class Demo : HAEntity
{
  // const EntityType __domain = EntityType::Demo;
  // Randomize device tracker data
  // Demonstrates using a device tracker to see where devices are located.
  class randomize_device_tracker_data_args
  {
  };
  void randomize_device_tracker_data(const randomize_device_tracker_data_args& args);
};

// START HEADER FOR Device_tracker

class Device_tracker : HAEntity
{
  // const EntityType __domain = EntityType::Device_tracker;
  // See
  // Records a seen tracked device.
  class see_args
  {
    optional<json> battery;
    optional<json> dev_id;
    optional<json> gps;
    optional<json> gps_accuracy;
    optional<json> host_name;
    optional<json> location_name;
    optional<json> mac;
  };
  void see(const see_args& args);
};

// START HEADER FOR Fan

class Fan : HAEntity
{
  // const EntityType __domain = EntityType::Fan;
  // Decrease speed
  // Decreases the speed of the fan.
  class decrease_speed_args
  {
    optional<json> percentage_step;
  };
  void decrease_speed(const decrease_speed_args& args);

  // Increase speed
  // Increases the speed of the fan.
  class increase_speed_args
  {
    optional<json> percentage_step;
  };
  void increase_speed(const increase_speed_args& args);

  // Oscillate
  // Controls oscillatation of the fan.
  class oscillate_args
  {
    optional<json> oscillating;
  };
  void oscillate(const oscillate_args& args);

  // Set direction
  // Sets the fan rotation direction.
  class set_direction_args
  {
    optional<json> direction;
  };
  void set_direction(const set_direction_args& args);

  // Set speed
  // Sets the fan speed.
  class set_percentage_args
  {
    optional<json> percentage;
  };
  void set_percentage(const set_percentage_args& args);

  // Set preset mode
  // Sets preset mode.
  class set_preset_mode_args
  {
    optional<json> preset_mode;
  };
  void set_preset_mode(const set_preset_mode_args& args);

  // Toggle
  // Toggles the fan on/off.
  class toggle_args
  {
  };
  void toggle(const toggle_args& args);

  // Turn off
  // Turns fan off.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Turns fan on.
  class turn_on_args
  {
    optional<json> percentage;
    optional<json> preset_mode;
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Ffmpeg

class Ffmpeg : HAEntity
{
  // const EntityType __domain = EntityType::Ffmpeg;
  // Restart
  // Sends a restart command to a ffmpeg based sensor.
  class restart_args
  {
    optional<json> entity_id;
  };
  void restart(const restart_args& args);

  // Start
  // Sends a start command to a ffmpeg based sensor.
  class start_args
  {
    optional<json> entity_id;
  };
  void start(const start_args& args);

  // Stop
  // Sends a stop command to a ffmpeg based sensor.
  class stop_args
  {
    optional<json> entity_id;
  };
  void stop(const stop_args& args);
};

// START HEADER FOR Frontend

class Frontend : HAEntity
{
  // const EntityType __domain = EntityType::Frontend;
  // Reload themes
  // Reloads themes from the YAML-configuration.
  class reload_themes_args
  {
  };
  void reload_themes(const reload_themes_args& args);

  // Set the default theme
  // Sets the default theme Home Assistant uses. Can be overridden by a user.
  class set_theme_args
  {
    optional<json> mode;
    optional<json> name;
  };
  void set_theme(const set_theme_args& args);
};

// START HEADER FOR Group

class Group : HAEntity
{
  // const EntityType __domain = EntityType::Group;
  // Reload
  // Reloads group configuration, entities, and notify services from YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);

  // Remove
  // Removes a group.
  class remove_args
  {
    optional<json> object_id;
  };
  void remove(const remove_args& args);

  // Set
  // Creates/Updates a user group.
  class set_args
  {
    optional<json> add_entities;
    optional<json> all;
    optional<json> entities;
    optional<json> icon;
    optional<json> name;
    optional<json> object_id;
    optional<json> remove_entities;
  };
  void set(const set_args& args);
};

// START HEADER FOR Homeassistant

class Homeassistant : HAEntity
{
  // const EntityType __domain = EntityType::Homeassistant;
  // Check configuration
  // Checks the Home Assistant YAML-configuration files for errors. Errors will be shown in the Home Assistant logs.
  class check_config_args
  {
  };
  void check_config(const check_config_args& args);

  // Reload all
  // Reload all YAML configuration that can be reloaded without restarting Home Assistant.
  class reload_all_args
  {
  };
  void reload_all(const reload_all_args& args);

  // Reload config entry
  // Reloads the specified config entry.
  class reload_config_entry_args
  {
    optional<json> entry_id;
  };
  void reload_config_entry(const reload_config_entry_args& args);

  // Reload core configuration
  // Reloads the core configuration from the YAML-configuration.
  class reload_core_config_args
  {
  };
  void reload_core_config(const reload_core_config_args& args);

  // Reload custom Jinja2 templates
  // Reloads Jinja2 templates found in the `custom_templates` folder in your config. New values will be applied on the next render of the template.
  class reload_custom_templates_args
  {
  };
  void reload_custom_templates(const reload_custom_templates_args& args);

  // Restart
  // Restarts Home Assistant.
  class restart_args
  {
  };
  void restart(const restart_args& args);

  // Save persistent states
  // Saves the persistent states immediately. Maintains the normal periodic saving interval.
  class save_persistent_states_args
  {
  };
  void save_persistent_states(const save_persistent_states_args& args);

  // Set location
  // Updates the Home Assistant location.
  class set_location_args
  {
    optional<json> elevation;
    optional<json> latitude;
    optional<json> longitude;
  };
  void set_location(const set_location_args& args);

  // Stop
  // Stops Home Assistant.
  class stop_args
  {
  };
  void stop(const stop_args& args);

  // Generic toggle
  // Generic service to toggle devices on/off under any domain.
  class toggle_args
  {
  };
  void toggle(const toggle_args& args);

  // Generic turn off
  // Generic service to turn devices off under any domain.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Generic turn on
  // Generic service to turn devices on under any domain.
  class turn_on_args
  {
  };
  void turn_on(const turn_on_args& args);

  // Update entity
  // Forces one or more entities to update its data.
  class update_entity_args
  {
  };
  void update_entity(const update_entity_args& args);
};

// START HEADER FOR Humidifier

class Humidifier : HAEntity
{
  // const EntityType __domain = EntityType::Humidifier;
  // Set humidity
  // Sets the target humidity.
  class set_humidity_args
  {
    optional<json> humidity;
  };
  void set_humidity(const set_humidity_args& args);

  // Set mode
  // Sets the humidifier operation mode.
  class set_mode_args
  {
    optional<json> mode;
  };
  void set_mode(const set_mode_args& args);

  // Toggle
  // Toggles the humidifier on/off.
  class toggle_args
  {
  };
  void toggle(const toggle_args& args);

  // Turn off
  // Turns the humidifier off.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Turns the humidifier on.
  class turn_on_args
  {
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Image_processing

class Image_processing : HAEntity
{
  // const EntityType __domain = EntityType::Image_processing;
  // Scan
  // Processes an image immediately.
  class scan_args
  {
  };
  void scan(const scan_args& args);
};

// START HEADER FOR Input_boolean

class Input_boolean : HAEntity
{
  // const EntityType __domain = EntityType::Input_boolean;
  // Reload
  // Reloads helpers from the YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);

  // Toggle
  // Toggles the helper on/off.
  class toggle_args
  {
  };
  void toggle(const toggle_args& args);

  // Turn off
  // Turns off the helper.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Turns on the helper.
  class turn_on_args
  {
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Input_button

class Input_button : HAEntity
{
  // const EntityType __domain = EntityType::Input_button;
  // Press
  // Mimics the physical button press on the device.
  class press_args
  {
  };
  void press(const press_args& args);

  // Reload
  // Reloads helpers from the YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);
};

// START HEADER FOR Input_datetime

class Input_datetime : HAEntity
{
  // const EntityType __domain = EntityType::Input_datetime;
  // Reload
  // Reloads helpers from the YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);

  // Set
  // Sets the date and/or time.
  class set_datetime_args
  {
    optional<json> date;
    optional<json> datetime;
    optional<json> time;
    optional<json> timestamp;
  };
  void set_datetime(const set_datetime_args& args);
};

// START HEADER FOR Input_number

class Input_number : HAEntity
{
  // const EntityType __domain = EntityType::Input_number;
  // Decrement
  // Decrements the current value by 1 step.
  class decrement_args
  {
  };
  void decrement(const decrement_args& args);

  // Increment
  // Increments the value by 1 step.
  class increment_args
  {
  };
  void increment(const increment_args& args);

  // Reload
  // Reloads helpers from the YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);

  // Set
  // Sets the value.
  class set_value_args
  {
    optional<json> value;
  };
  void set_value(const set_value_args& args);
};

// START HEADER FOR Input_select

class Input_select : HAEntity
{
  // const EntityType __domain = EntityType::Input_select;
  // Reload
  // Reloads helpers from the YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);

  // First
  // Selects the first option.
  class select_first_args
  {
  };
  void select_first(const select_first_args& args);

  // Last
  // Selects the last option.
  class select_last_args
  {
  };
  void select_last(const select_last_args& args);

  // Next
  // Select the next option.
  class select_next_args
  {
    optional<json> cycle;
  };
  void select_next(const select_next_args& args);

  // Select
  // Selects an option.
  class select_option_args
  {
    optional<json> option;
  };
  void select_option(const select_option_args& args);

  // Previous
  // Selects the previous option.
  class select_previous_args
  {
    optional<json> cycle;
  };
  void select_previous(const select_previous_args& args);

  // Set options
  // Sets the options.
  class set_options_args
  {
    optional<json> options;
  };
  void set_options(const set_options_args& args);
};

// START HEADER FOR Input_text

class Input_text : HAEntity
{
  // const EntityType __domain = EntityType::Input_text;
  // Reload
  // Reloads helpers from the YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);

  // Set
  // Sets the value.
  class set_value_args
  {
    optional<json> value;
  };
  void set_value(const set_value_args& args);
};

// START HEADER FOR Light

class Light : HAEntity
{
  // const EntityType __domain = EntityType::Light;
  // Toggle
  // Toggles one or more lights, from on to off, or, off to on, based on their current state.
  class toggle_args
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
  void toggle(const toggle_args& args);

  // Turn off
  // Turn off one or more lights.
  class turn_off_args
  {
    optional<json> flash;
    optional<json> transition;
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Turn on one or more lights and adjust properties of the light, even when they are turned on already.
  class turn_on_args
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
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Lock

class Lock : HAEntity
{
  // const EntityType __domain = EntityType::Lock;
  // Lock
  // Locks a lock.
  class lock_args
  {
    optional<json> code;
  };
  void lock(const lock_args& args);

  // Open
  // Opens a lock.
  class open_args
  {
    optional<json> code;
  };
  void open(const open_args& args);

  // Unlock
  // Unlocks a lock.
  class unlock_args
  {
    optional<json> code;
  };
  void unlock(const unlock_args& args);
};

// START HEADER FOR Logbook

class Logbook : HAEntity
{
  // const EntityType __domain = EntityType::Logbook;
  // Log
  // Creates a custom entry in the logbook.
  class log_args
  {
    optional<json> domain;
    optional<json> entity_id;
    optional<json> message;
    optional<json> name;
  };
  void log(const log_args& args);
};

// START HEADER FOR Logger

class Logger : HAEntity
{
  // const EntityType __domain = EntityType::Logger;
  // Set default level
  // Sets the default log level for integrations.
  class set_default_level_args
  {
    optional<json> level;
  };
  void set_default_level(const set_default_level_args& args);

  // Set level
  // Sets the log level for one or more integrations.
  class set_level_args
  {
  };
  void set_level(const set_level_args& args);
};

// START HEADER FOR Media_player

class Media_player : HAEntity
{
  // const EntityType __domain = EntityType::Media_player;
  // Clear playlist
  // Clears the playlist.
  class clear_playlist_args
  {
  };
  void clear_playlist(const clear_playlist_args& args);

  // Join
  // Groups media players together for synchronous playback. Only works on supported multiroom audio systems.
  class join_args
  {
    optional<json> group_members;
  };
  void join(const join_args& args);

  // Next
  // Selects the next track.
  class media_next_track_args
  {
  };
  void media_next_track(const media_next_track_args& args);

  // Pause
  // Pauses.
  class media_pause_args
  {
  };
  void media_pause(const media_pause_args& args);

  // Play
  // Starts playing.
  class media_play_args
  {
  };
  void media_play(const media_play_args& args);

  // Play/Pause
  // Toggles play/pause.
  class media_play_pause_args
  {
  };
  void media_play_pause(const media_play_pause_args& args);

  // Previous
  // Selects the previous track.
  class media_previous_track_args
  {
  };
  void media_previous_track(const media_previous_track_args& args);

  // Seek
  // Allows you to go to a different part of the media that is currently playing.
  class media_seek_args
  {
    optional<json> seek_position;
  };
  void media_seek(const media_seek_args& args);

  // Stop
  // Stops playing.
  class media_stop_args
  {
  };
  void media_stop(const media_stop_args& args);

  // Play media
  // Starts playing specified media.
  class play_media_args
  {
    optional<json> announce;
    optional<json> enqueue;
    optional<json> media_content_id;
    optional<json> media_content_type;
  };
  void play_media(const play_media_args& args);

  // Repeat
  // Playback mode that plays the media in a loop.
  class repeat_set_args
  {
    optional<json> repeat;
  };
  void repeat_set(const repeat_set_args& args);

  // Select sound mode
  // Selects a specific sound mode.
  class select_sound_mode_args
  {
    optional<json> sound_mode;
  };
  void select_sound_mode(const select_sound_mode_args& args);

  // Select source
  // Sends the media player the command to change input source.
  class select_source_args
  {
    optional<json> source;
  };
  void select_source(const select_source_args& args);

  // Shuffle
  // Playback mode that selects the media in randomized order.
  class shuffle_set_args
  {
    optional<json> shuffle;
  };
  void shuffle_set(const shuffle_set_args& args);

  // Toggle
  // Toggles a media player on/off.
  class toggle_args
  {
  };
  void toggle(const toggle_args& args);

  // Turn off
  // Turns off the power of the media player.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Turns on the power of the media player.
  class turn_on_args
  {
  };
  void turn_on(const turn_on_args& args);

  // Unjoin
  // Removes the player from a group. Only works on platforms which support player groups.
  class unjoin_args
  {
  };
  void unjoin(const unjoin_args& args);

  // Turn down volume
  // Turns down the volume.
  class volume_down_args
  {
  };
  void volume_down(const volume_down_args& args);

  // Mute/unmute volume
  // Mutes or unmutes the media player.
  class volume_mute_args
  {
    optional<json> is_volume_muted;
  };
  void volume_mute(const volume_mute_args& args);

  // Set volume
  // Sets the volume level.
  class volume_set_args
  {
    optional<json> volume_level;
  };
  void volume_set(const volume_set_args& args);

  // Turn up volume
  // Turns up the volume.
  class volume_up_args
  {
  };
  void volume_up(const volume_up_args& args);
};

// START HEADER FOR Notify

class Notify : HAEntity
{
  // const EntityType __domain = EntityType::Notify;
  // Send a notification via demo_test_target_name
  // Sends a notification message using the demo_test_target_name integration.
  class demo_test_target_name_args
  {
    optional<json> data;
    optional<json> message;
    optional<json> target;
    optional<json> title;
  };
  void demo_test_target_name(const demo_test_target_name_args& args);

  // Send a notification with notify
  // Sends a notification message using the notify service.
  class notify_args
  {
    optional<json> data;
    optional<json> message;
    optional<json> target;
    optional<json> title;
  };
  void notify(const notify_args& args);

  // Send a persistent notification
  // Sends a notification that is visible in the **Notifications** panel.
  class persistent_notification_args
  {
    optional<json> data;
    optional<json> message;
    optional<json> title;
  };
  void persistent_notification(const persistent_notification_args& args);
};

// START HEADER FOR Number

class Number : HAEntity
{
  // const EntityType __domain = EntityType::Number;
  // Set
  // Sets the value of a number.
  class set_value_args
  {
    optional<json> value;
  };
  void set_value(const set_value_args& args);
};

// START HEADER FOR Persistent_notification

class Persistent_notification : HAEntity
{
  // const EntityType __domain = EntityType::Persistent_notification;
  // Create
  // Shows a notification on the **Notifications** panel.
  class create_args
  {
    optional<json> message;
    optional<json> notification_id;
    optional<json> title;
  };
  void create(const create_args& args);

  // Dismiss
  // Removes a notification from the **Notifications** panel.
  class dismiss_args
  {
    optional<json> notification_id;
  };
  void dismiss(const dismiss_args& args);

  // Dismiss all
  // Removes all notifications from the **Notifications** panel.
  class dismiss_all_args
  {
  };
  void dismiss_all(const dismiss_all_args& args);
};

// START HEADER FOR Person

class Person : HAEntity
{
  // const EntityType __domain = EntityType::Person;
  // Reload
  // Reloads persons from the YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);
};

// START HEADER FOR Recorder

class Recorder : HAEntity
{
  // const EntityType __domain = EntityType::Recorder;
  // Disable
  // Stops the recording of events and state changes.
  class disable_args
  {
  };
  void disable(const disable_args& args);

  // Enable
  // Starts the recording of events and state changes.
  class enable_args
  {
  };
  void enable(const enable_args& args);

  // Purge
  // Starts purge task - to clean up old data from your database.
  class purge_args
  {
    optional<json> apply_filter;
    optional<json> keep_days;
    optional<json> repack;
  };
  void purge(const purge_args& args);

  // Purge entities
  // Starts a purge task to remove the data related to specific entities from your database.
  class purge_entities_args
  {
    optional<json> domains;
    optional<json> entity_globs;
    optional<json> keep_days;
  };
  void purge_entities(const purge_entities_args& args);
};

// START HEADER FOR Scene

class Scene : HAEntity
{
  // const EntityType __domain = EntityType::Scene;
  // Apply
  // Activates a scene with configuration.
  class apply_args
  {
    optional<json> entities;
    optional<json> transition;
  };
  void apply(const apply_args& args);

  // Create
  // Creates a new scene.
  class create_args
  {
    optional<json> entities;
    optional<json> scene_id;
    optional<json> snapshot_entities;
  };
  void create(const create_args& args);

  // Delete
  // Deletes a dynamically created scene.
  class delete_args
  {
  };
  void _delete(const delete_args& args);

  // Reload
  // Reloads the scenes from the YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);

  // Activate
  // Activates a scene.
  class turn_on_args
  {
    optional<json> transition;
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Schedule

class Schedule : HAEntity
{
  // const EntityType __domain = EntityType::Schedule;
  // Reload
  // Reloads schedules from the YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);
};

// START HEADER FOR Script

class Script : HAEntity
{
  // const EntityType __domain = EntityType::Script;
  // Reload
  // Reloads all the available scripts.
  class reload_args
  {
  };
  void reload(const reload_args& args);

  // Toggle
  // Toggle a script. Starts it, if isn't running, stops it otherwise.
  class toggle_args
  {
  };
  void toggle(const toggle_args& args);

  // Turn off
  // Stops a running script.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Runs the sequence of actions defined in a script.
  class turn_on_args
  {
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Select

class Select : HAEntity
{
  // const EntityType __domain = EntityType::Select;
  // First
  // Selects the first option.
  class select_first_args
  {
  };
  void select_first(const select_first_args& args);

  // Last
  // Selects the last option.
  class select_last_args
  {
  };
  void select_last(const select_last_args& args);

  // Next
  // Selects the next option.
  class select_next_args
  {
    optional<json> cycle;
  };
  void select_next(const select_next_args& args);

  // Select
  // Selects an option.
  class select_option_args
  {
    optional<json> option;
  };
  void select_option(const select_option_args& args);

  // Previous
  // Selects the previous option.
  class select_previous_args
  {
    optional<json> cycle;
  };
  void select_previous(const select_previous_args& args);
};

// START HEADER FOR Shopping_list

class Shopping_list : HAEntity
{
  // const EntityType __domain = EntityType::Shopping_list;
  // Add item
  // Adds an item to the shopping list.
  class add_item_args
  {
    optional<json> name;
  };
  void add_item(const add_item_args& args);

  // Clear completed items
  // Clears completed items from the shopping list.
  class clear_completed_items_args
  {
  };
  void clear_completed_items(const clear_completed_items_args& args);

  // Complete all
  // Marks all items as completed in the shopping list (without removing them from the list).
  class complete_all_args
  {
  };
  void complete_all(const complete_all_args& args);

  // Complete item
  // Marks the first item with matching name as completed in the shopping list.
  class complete_item_args
  {
    optional<json> name;
  };
  void complete_item(const complete_item_args& args);

  // Incomplete all
  // Marks all items as incomplete in the shopping list.
  class incomplete_all_args
  {
  };
  void incomplete_all(const incomplete_all_args& args);

  // Incomplete item
  // Marks the first item with matching name as incomplete in the shopping list.
  class incomplete_item_args
  {
    optional<json> name;
  };
  void incomplete_item(const incomplete_item_args& args);

  // Remove item
  // Removes the first item with matching name from the shopping list.
  class remove_item_args
  {
    optional<json> name;
  };
  void remove_item(const remove_item_args& args);

  // Sort all items
  // Sorts all items by name in the shopping list.
  class sort_args
  {
    optional<json> reverse;
  };
  void sort(const sort_args& args);
};

// START HEADER FOR Siren

class Siren : HAEntity
{
  // const EntityType __domain = EntityType::Siren;
  // Toggle
  // Toggles the siren on/off.
  class toggle_args
  {
  };
  void toggle(const toggle_args& args);

  // Turn off
  // Turns the siren off.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Turns the siren on.
  class turn_on_args
  {
    optional<json> duration;
    optional<json> tone;
    optional<json> volume_level;
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Switch

class Switch : HAEntity
{
  // const EntityType __domain = EntityType::Switch;
  // Toggle
  // Toggles a switch on/off.
  class toggle_args
  {
  };
  void toggle(const toggle_args& args);

  // Turn off
  // Turns a switch off.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Turns a switch on.
  class turn_on_args
  {
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR System_log

class System_log : HAEntity
{
  // const EntityType __domain = EntityType::System_log;
  // Clear all
  // Clears all log entries.
  class clear_args
  {
  };
  void clear(const clear_args& args);

  // Write
  // Write log entry.
  class write_args
  {
    optional<json> level;
    optional<json> logger;
    optional<json> message;
  };
  void write(const write_args& args);
};

// START HEADER FOR Text

class Text : HAEntity
{
  // const EntityType __domain = EntityType::Text;
  // Set value
  // Sets the value.
  class set_value_args
  {
    optional<json> value;
  };
  void set_value(const set_value_args& args);
};

// START HEADER FOR Time

class Time : HAEntity
{
  // const EntityType __domain = EntityType::Time;
  // Set Time
  // Sets the time.
  class set_value_args
  {
    optional<json> time;
  };
  void set_value(const set_value_args& args);
};

// START HEADER FOR Timer

class Timer : HAEntity
{
  // const EntityType __domain = EntityType::Timer;
  // Cancel
  // Cancels a timer.
  class cancel_args
  {
  };
  void cancel(const cancel_args& args);

  // Change
  // Changes a timer.
  class change_args
  {
    optional<json> duration;
  };
  void change(const change_args& args);

  // Finish
  // Finishes a timer.
  class finish_args
  {
  };
  void finish(const finish_args& args);

  // Pause
  // Pauses a timer.
  class pause_args
  {
  };
  void pause(const pause_args& args);

  // Reload
  // Reloads timers from the YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);

  // Start
  // Starts a timer.
  class start_args
  {
    optional<json> duration;
  };
  void start(const start_args& args);
};

// START HEADER FOR Todo

class Todo : HAEntity
{
  // const EntityType __domain = EntityType::Todo;
  // Add to-do list item
  // Add a new to-do list item.
  class add_item_args
  {
    optional<json> description;
    optional<json> due_date;
    optional<json> due_datetime;
    optional<json> item;
  };
  void add_item(const add_item_args& args);

  // Get to-do list items
  // Get items on a to-do list.
  class get_items_args
  {
    optional<json> status;
  };
  void get_items(const get_items_args& args);

  // Remove all completed to-do list items
  // Remove all to-do list items that have been completed.
  class remove_completed_items_args
  {
  };
  void remove_completed_items(const remove_completed_items_args& args);

  // Remove a to-do list item
  // Remove an existing to-do list item by its name.
  class remove_item_args
  {
    optional<json> item;
  };
  void remove_item(const remove_item_args& args);

  // Update to-do list item
  // Update an existing to-do list item based on its name.
  class update_item_args
  {
    optional<json> description;
    optional<json> due_date;
    optional<json> due_datetime;
    optional<json> item;
    optional<json> rename;
    optional<json> status;
  };
  void update_item(const update_item_args& args);
};

// START HEADER FOR Tts

class Tts : HAEntity
{
  // const EntityType __domain = EntityType::Tts;
  // Clear TTS cache
  // Removes all cached text-to-speech files and purges the memory.
  class clear_cache_args
  {
  };
  void clear_cache(const clear_cache_args& args);

  // Say a TTS message with demo
  // Say something using text-to-speech on a media player with demo.
  class demo_say_args
  {
    optional<json> cache;
    optional<json> entity_id;
    optional<json> language;
    optional<json> message;
    optional<json> options;
  };
  void demo_say(const demo_say_args& args);

  // Speak
  // Speaks something using text-to-speech on a media player.
  class speak_args
  {
    optional<json> cache;
    optional<json> language;
    optional<json> media_player_entity_id;
    optional<json> message;
    optional<json> options;
  };
  void speak(const speak_args& args);
};

// START HEADER FOR Update

class Update : HAEntity
{
  // const EntityType __domain = EntityType::Update;
  // Clear skipped update
  // Removes the skipped version marker from an update.
  class clear_skipped_args
  {
  };
  void clear_skipped(const clear_skipped_args& args);

  // Install update
  // Installs an update for this device or service.
  class install_args
  {
    optional<json> backup;
    optional<json> version;
  };
  void install(const install_args& args);

  // Skip update
  // Marks currently available update as skipped.
  class skip_args
  {
  };
  void skip(const skip_args& args);
};

// START HEADER FOR Vacuum

class Vacuum : HAEntity
{
  // const EntityType __domain = EntityType::Vacuum;
  // Clean spot
  // Tells the vacuum cleaner to do a spot clean-up.
  class clean_spot_args
  {
  };
  void clean_spot(const clean_spot_args& args);

  // Locate
  // Locates the vacuum cleaner robot.
  class locate_args
  {
  };
  void locate(const locate_args& args);

  // Pause
  // Pauses the cleaning task.
  class pause_args
  {
  };
  void pause(const pause_args& args);

  // Return to dock
  // Tells the vacuum cleaner to return to its dock.
  class return_to_base_args
  {
  };
  void return_to_base(const return_to_base_args& args);

  // Send command
  // Sends a command to the vacuum cleaner.
  class send_command_args
  {
    optional<json> command;
    optional<json> params;
  };
  void send_command(const send_command_args& args);

  // Set fan speed
  // Sets the fan speed of the vacuum cleaner.
  class set_fan_speed_args
  {
    optional<json> fan_speed;
  };
  void set_fan_speed(const set_fan_speed_args& args);

  // Start
  // Starts or resumes the cleaning task.
  class start_args
  {
  };
  void start(const start_args& args);

  // Start/pause
  // Starts, pauses, or resumes the cleaning task.
  class start_pause_args
  {
  };
  void start_pause(const start_pause_args& args);

  // Stop
  // Stops the current cleaning task.
  class stop_args
  {
  };
  void stop(const stop_args& args);

  // Toggle
  // Toggles the vacuum cleaner on/off.
  class toggle_args
  {
  };
  void toggle(const toggle_args& args);

  // Turn off
  // Stops the current cleaning task and returns to its dock.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Starts a new cleaning task.
  class turn_on_args
  {
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Water_heater

class Water_heater : HAEntity
{
  // const EntityType __domain = EntityType::Water_heater;
  // Set away mode
  // Turns away mode on/off.
  class set_away_mode_args
  {
    optional<json> away_mode;
  };
  void set_away_mode(const set_away_mode_args& args);

  // Set operation mode
  // Sets the operation mode.
  class set_operation_mode_args
  {
    optional<json> operation_mode;
  };
  void set_operation_mode(const set_operation_mode_args& args);

  // Set temperature
  // Sets the target temperature.
  class set_temperature_args
  {
    optional<json> operation_mode;
    optional<json> temperature;
  };
  void set_temperature(const set_temperature_args& args);

  // Turn off
  // Turns water heater off.
  class turn_off_args
  {
  };
  void turn_off(const turn_off_args& args);

  // Turn on
  // Turns water heater on.
  class turn_on_args
  {
  };
  void turn_on(const turn_on_args& args);
};

// START HEADER FOR Weather

class Weather : HAEntity
{
  // const EntityType __domain = EntityType::Weather;
  // Get forecast
  // Get weather forecast.
  class get_forecast_args
  {
    optional<json> type;
  };
  void get_forecast(const get_forecast_args& args);

  // Get forecasts
  // Get weather forecasts.
  class get_forecasts_args
  {
    optional<json> type;
  };
  void get_forecasts(const get_forecasts_args& args);
};

// START HEADER FOR Zone

class Zone : HAEntity
{
  // const EntityType __domain = EntityType::Zone;
  // Reload
  // Reloads zones from the YAML-configuration.
  class reload_args
  {
  };
  void reload(const reload_args& args);
};

}
