#pragma once
#include <cstdint>

namespace me {
namespace skywatcher {

enum MountError : char {
  ME_UNKNOWN_COMMAND = '0',
  ME_LENGTH_ERROR = '1',
  ME_INVALID_CHAR = '2',
  ME_UNINITIALIZED = '3',
  ME_SLEEPING = '4',
  ME_PEC_TRAINING_RUNNING = '5',
  ME_NO_VALID_PEC_DATA = '6',
};

enum MountAxis : char {
  MA_1 = '1',    // RA/Azm
  MA_2 = '2',    // DEC/Alt
  MA_BOTH = '3', //
};

enum CommandType : char {
  SetPosition = 'E',
  InitializationDone = 'F',
  SetMotionMode = 'G',
  SetGotoTargetIncrement = 'H', // grey
  SetBrakePointIncrement = 'M', // grey
  SetGotoTarget = 'S',
  SetStepPeriod = 'I',
  SetLongGotoStepPeriod = 'T', // grey
  SetBrakeSteps = 'U',         // grey
  StartMotion = 'J',
  StopMotion = 'K',
  InstantStop = 'L',
  SetSleep = 'B',
  SetAuxSwitchOnOff = 'O',
  SetAutoguideSpeed = 'P',
  RunBootloaderMode = 'Q',
  SetPolarScopeLEDBrightness = 'V',
  InquireCountsPerRevolution = 'a',
  InquireTimerInteruptFrequency = 'b',
  InquireBrakeSteps = 'c', // grey
  InquireGotoTargetPosition = 'h',
  InquireStepPeriod = 'i',
  InquirePosition = 'j',
  InquireIncrement = 'k',  // grey
  InquireBrakePoint = 'm', // grey
  InquireStatus = 'f',
  InquireHighSpeedRatio = 'g',
  Inquire1XTrackingPeriod = 'D',
  InquireTeleAxisPosition = 'd',
  InquireMotorBoardVersion = 'e',
  InquirePECPeriod = 's', // grey
  SetDebugFlag = 'z',
  ExtendedSettings = 'W',
  ExtendedInquire = 'q',
  SetEEPROMAddress = 'C',     // grey
  SetEEPROMValue = 'N',       // grey
  InquireEEPROMValue = 'n',   // grey
  SetRegisterAddress = 'A',   // grey
  SetRegisterValue = 'R',     // grey
  InquireRegisterValue = 'r', // grey
};

enum GetFeature {
  GetIndexerCmd = 0x00,
  GetFeaturesCmd = 0x01,
};

enum SetFeature : uint32_t {
  START_PEC_TRAINING = 0x00,
  CANCEL_PEC_TRAINING = 0x01,
  START_PEC_TRACKING = 0x02,
  CANCEL_PEC_TRACKING = 0x03,
  ENABLE_DUAL_ENCODER = 0x04,
  DISABLE_DUAL_ENCODER = 0x05,
  ENABLE_FULL_CURRENT_LOW_SPEED_CMD = 0x107,
  DISABLE_FULL_CURRENT_LOW_SPEED_CMD = 0x06,
  SET_STRIDE_FOR_SLEWING = 0x07,
  RESET_INDEXER_POSITION = 0x08,
  WRITE_RAM_FLASH_TO_ROM = 0x09,
};

enum SleepMode : char {
  SM_WAKEUP = '1',
  SM_SLEEP = '2',
};

enum AuxSwitch : char {
  AS_ON = '0',
  AS_OFF = '1',
};

enum AutoGuideSpeed : char {
  AG_1x = '0',
  AG_075x = '1',
  AG_05x = '2',
  AG_025x = '3',
  AG_0125x = '4',
};

enum MotionMode : char {
  HighSpeedGoto = '0',
  LowSpeedTracking = '1',
  LowSpeedGoto = '2',
  HighSpeedTracking = '3',
};

enum MotionDirection : char {
  Forward = '0',
  Reverse = '1',
};

struct MountStatus {
  bool Tracking;
  bool CCW;
  bool Fast;
  bool Running;
  bool Blocked;
  bool Initialized;
  bool LevelSwitchOn;
};

struct MotorBoardVersion {
  uint32_t Major;
  uint32_t Minor;
  bool IsEqMount;
};

} // namespace skywatcher
} // namespace me
