// Licensed GNU LGPL v2.1 or later: http://www.gnu.org/licenses/lgpl.html
#ifndef __BSE_ENUMS_H__
#define __BSE_ENUMS_H__

#include <bse/gsldefs.hh>
#include <bse/bsetype.hh>
#include <bse/bseserverapi.hh>


G_BEGIN_DECLS


/* --- enum definitions --- */
typedef enum
{
  BSE_IIR_FILTER_BUTTERWORTH = 1,
  BSE_IIR_FILTER_BESSEL      = 2,
  BSE_IIR_FILTER_CHEBYSHEV1  = 3,
  BSE_IIR_FILTER_CHEBYSHEV2  = 4,
  BSE_IIR_FILTER_ELLIPTIC    = 5,
} BseIIRFilterKind;
typedef enum
{
  BSE_IIR_FILTER_LOW_PASS    = 1,
  BSE_IIR_FILTER_BAND_PASS   = 2,
  BSE_IIR_FILTER_HIGH_PASS   = 3,
  BSE_IIR_FILTER_BAND_STOP   = 4,
} BseIIRFilterType;
typedef enum
{
  BSE_REGISTER_PLUGIN   = 1,
  BSE_REGISTER_SCRIPT   = 2,
  BSE_REGISTER_DONE	= 256
} BseRegistrationType;
typedef enum
{
  BSE_INTERPOL_NONE,		/*< nick=None >*/
  BSE_INTERPOL_LINEAR,		/*< nick=Linear >*/
  BSE_INTERPOL_CUBIC		/*< nick=Cubic >*/
} BseInterpolType;
typedef enum
{
  BSE_LOOP_NONE,
  BSE_LOOP_PATTERN,
  BSE_LOOP_PATTERN_ROWS,
  BSE_LOOP_SONG,
  BSE_LOOP_LAST				/*< skip >*/
} BseLoopType;
typedef enum
{
  BSE_MAGIC_BSE_BIN_EXTENSION   = 1 << 0,
  BSE_MAGIC_BSE_SONG            = 1 << 2
} BseMagicFlags;

#ifdef  BSE_IDL_SURROGATES
typedef enum
{
  BSE_ERROR_NONE = Bse::Error::NONE,
  BSE_ERROR_INTERNAL = Bse::Error::INTERNAL,
  BSE_ERROR_UNKNOWN = Bse::Error::UNKNOWN,
  BSE_ERROR_IO = Bse::Error::IO,
  BSE_ERROR_PERMS = Bse::Error::PERMS,
  BSE_ERROR_FILE_BUSY = Bse::Error::FILE_BUSY,
  BSE_ERROR_FILE_EXISTS = Bse::Error::FILE_EXISTS,
  BSE_ERROR_FILE_EOF = Bse::Error::FILE_EOF,
  BSE_ERROR_FILE_EMPTY = Bse::Error::FILE_EMPTY,
  BSE_ERROR_FILE_NOT_FOUND = Bse::Error::FILE_NOT_FOUND,
  BSE_ERROR_FILE_IS_DIR = Bse::Error::FILE_IS_DIR,
  BSE_ERROR_FILE_OPEN_FAILED = Bse::Error::FILE_OPEN_FAILED,
  BSE_ERROR_FILE_SEEK_FAILED = Bse::Error::FILE_SEEK_FAILED,
  BSE_ERROR_FILE_READ_FAILED = Bse::Error::FILE_READ_FAILED,
  BSE_ERROR_FILE_WRITE_FAILED = Bse::Error::FILE_WRITE_FAILED,
  BSE_ERROR_MANY_FILES = Bse::Error::MANY_FILES,
  BSE_ERROR_NO_FILES = Bse::Error::NO_FILES,
  BSE_ERROR_NO_SPACE = Bse::Error::NO_SPACE,
  BSE_ERROR_NO_MEMORY = Bse::Error::NO_MEMORY,
  BSE_ERROR_NO_HEADER = Bse::Error::NO_HEADER,
  BSE_ERROR_NO_SEEK_INFO = Bse::Error::NO_SEEK_INFO,
  BSE_ERROR_NO_DATA = Bse::Error::NO_DATA,
  BSE_ERROR_DATA_CORRUPT = Bse::Error::DATA_CORRUPT,
  BSE_ERROR_WRONG_N_CHANNELS = Bse::Error::WRONG_N_CHANNELS,
  BSE_ERROR_FORMAT_INVALID = Bse::Error::FORMAT_INVALID,
  BSE_ERROR_FORMAT_UNKNOWN = Bse::Error::FORMAT_UNKNOWN,
  BSE_ERROR_DATA_UNMATCHED = Bse::Error::DATA_UNMATCHED,
  BSE_ERROR_TEMP = Bse::Error::TEMP,
  BSE_ERROR_WAVE_NOT_FOUND = Bse::Error::WAVE_NOT_FOUND,
  BSE_ERROR_CODEC_FAILURE = Bse::Error::CODEC_FAILURE,
  BSE_ERROR_UNIMPLEMENTED = Bse::Error::UNIMPLEMENTED,
  BSE_ERROR_INVALID_PROPERTY = Bse::Error::INVALID_PROPERTY,
  BSE_ERROR_INVALID_MIDI_CONTROL = Bse::Error::INVALID_MIDI_CONTROL,
  BSE_ERROR_PARSE_ERROR = Bse::Error::PARSE_ERROR,
  BSE_ERROR_SPAWN = Bse::Error::SPAWN,
  BSE_ERROR_DEVICE_NOT_AVAILABLE = Bse::Error::DEVICE_NOT_AVAILABLE,
  BSE_ERROR_DEVICE_ASYNC = Bse::Error::DEVICE_ASYNC,
  BSE_ERROR_DEVICE_BUSY = Bse::Error::DEVICE_BUSY,
  BSE_ERROR_DEVICE_FORMAT = Bse::Error::DEVICE_FORMAT,
  BSE_ERROR_DEVICE_BUFFER = Bse::Error::DEVICE_BUFFER,
  BSE_ERROR_DEVICE_LATENCY = Bse::Error::DEVICE_LATENCY,
  BSE_ERROR_DEVICE_CHANNELS = Bse::Error::DEVICE_CHANNELS,
  BSE_ERROR_DEVICE_FREQUENCY = Bse::Error::DEVICE_FREQUENCY,
  BSE_ERROR_DEVICES_MISMATCH = Bse::Error::DEVICES_MISMATCH,
  BSE_ERROR_SOURCE_NO_SUCH_MODULE = Bse::Error::SOURCE_NO_SUCH_MODULE,
  BSE_ERROR_SOURCE_NO_SUCH_ICHANNEL = Bse::Error::SOURCE_NO_SUCH_ICHANNEL,
  BSE_ERROR_SOURCE_NO_SUCH_OCHANNEL = Bse::Error::SOURCE_NO_SUCH_OCHANNEL,
  BSE_ERROR_SOURCE_NO_SUCH_CONNECTION = Bse::Error::SOURCE_NO_SUCH_CONNECTION,
  BSE_ERROR_SOURCE_PRIVATE_ICHANNEL = Bse::Error::SOURCE_PRIVATE_ICHANNEL,
  BSE_ERROR_SOURCE_ICHANNEL_IN_USE = Bse::Error::SOURCE_ICHANNEL_IN_USE,
  BSE_ERROR_SOURCE_CHANNELS_CONNECTED = Bse::Error::SOURCE_CHANNELS_CONNECTED,
  BSE_ERROR_SOURCE_CONNECTION_INVALID = Bse::Error::SOURCE_CONNECTION_INVALID,
  BSE_ERROR_SOURCE_PARENT_MISMATCH = Bse::Error::SOURCE_PARENT_MISMATCH,
  BSE_ERROR_SOURCE_BAD_LOOPBACK = Bse::Error::SOURCE_BAD_LOOPBACK,
  BSE_ERROR_SOURCE_BUSY = Bse::Error::SOURCE_BUSY,
  BSE_ERROR_SOURCE_TYPE_INVALID = Bse::Error::SOURCE_TYPE_INVALID,
  BSE_ERROR_PROC_NOT_FOUND = Bse::Error::PROC_NOT_FOUND,
  BSE_ERROR_PROC_BUSY = Bse::Error::PROC_BUSY,
  BSE_ERROR_PROC_PARAM_INVAL = Bse::Error::PROC_PARAM_INVAL,
  BSE_ERROR_PROC_EXECUTION = Bse::Error::PROC_EXECUTION,
  BSE_ERROR_PROC_ABORT = Bse::Error::PROC_ABORT,
  BSE_ERROR_NO_ENTRY = Bse::Error::NO_ENTRY,
  BSE_ERROR_NO_EVENT = Bse::Error::NO_EVENT,
  BSE_ERROR_NO_TARGET = Bse::Error::NO_TARGET,
  BSE_ERROR_NOT_OWNER = Bse::Error::NOT_OWNER,
  BSE_ERROR_INVALID_OFFSET = Bse::Error::INVALID_OFFSET,
  BSE_ERROR_INVALID_DURATION = Bse::Error::INVALID_DURATION,
  BSE_ERROR_INVALID_OVERLAP = Bse::Error::INVALID_OVERLAP,
} BseErrorType;
typedef enum
{
  BSE_MIDI_SIGNAL_PROGRAM = Bse::MidiSignal::PROGRAM,
  BSE_MIDI_SIGNAL_PRESSURE = Bse::MidiSignal::PRESSURE,
  BSE_MIDI_SIGNAL_PITCH_BEND = Bse::MidiSignal::PITCH_BEND,
  BSE_MIDI_SIGNAL_VELOCITY = Bse::MidiSignal::VELOCITY,
  BSE_MIDI_SIGNAL_FINE_TUNE = Bse::MidiSignal::FINE_TUNE,
  BSE_MIDI_SIGNAL_CONTINUOUS_0 = Bse::MidiSignal::CONTINUOUS_0,
  BSE_MIDI_SIGNAL_CONTINUOUS_1 = Bse::MidiSignal::CONTINUOUS_1,
  BSE_MIDI_SIGNAL_CONTINUOUS_2 = Bse::MidiSignal::CONTINUOUS_2,
  BSE_MIDI_SIGNAL_CONTINUOUS_3 = Bse::MidiSignal::CONTINUOUS_3,
  BSE_MIDI_SIGNAL_CONTINUOUS_4 = Bse::MidiSignal::CONTINUOUS_4,
  BSE_MIDI_SIGNAL_CONTINUOUS_5 = Bse::MidiSignal::CONTINUOUS_5,
  BSE_MIDI_SIGNAL_CONTINUOUS_6 = Bse::MidiSignal::CONTINUOUS_6,
  BSE_MIDI_SIGNAL_CONTINUOUS_7 = Bse::MidiSignal::CONTINUOUS_7,
  BSE_MIDI_SIGNAL_CONTINUOUS_8 = Bse::MidiSignal::CONTINUOUS_8,
  BSE_MIDI_SIGNAL_CONTINUOUS_9 = Bse::MidiSignal::CONTINUOUS_9,
  BSE_MIDI_SIGNAL_CONTINUOUS_10 = Bse::MidiSignal::CONTINUOUS_10,
  BSE_MIDI_SIGNAL_CONTINUOUS_11 = Bse::MidiSignal::CONTINUOUS_11,
  BSE_MIDI_SIGNAL_CONTINUOUS_12 = Bse::MidiSignal::CONTINUOUS_12,
  BSE_MIDI_SIGNAL_CONTINUOUS_13 = Bse::MidiSignal::CONTINUOUS_13,
  BSE_MIDI_SIGNAL_CONTINUOUS_14 = Bse::MidiSignal::CONTINUOUS_14,
  BSE_MIDI_SIGNAL_CONTINUOUS_15 = Bse::MidiSignal::CONTINUOUS_15,
  BSE_MIDI_SIGNAL_CONTINUOUS_16 = Bse::MidiSignal::CONTINUOUS_16,
  BSE_MIDI_SIGNAL_CONTINUOUS_17 = Bse::MidiSignal::CONTINUOUS_17,
  BSE_MIDI_SIGNAL_CONTINUOUS_18 = Bse::MidiSignal::CONTINUOUS_18,
  BSE_MIDI_SIGNAL_CONTINUOUS_19 = Bse::MidiSignal::CONTINUOUS_19,
  BSE_MIDI_SIGNAL_CONTINUOUS_20 = Bse::MidiSignal::CONTINUOUS_20,
  BSE_MIDI_SIGNAL_CONTINUOUS_21 = Bse::MidiSignal::CONTINUOUS_21,
  BSE_MIDI_SIGNAL_CONTINUOUS_22 = Bse::MidiSignal::CONTINUOUS_22,
  BSE_MIDI_SIGNAL_CONTINUOUS_23 = Bse::MidiSignal::CONTINUOUS_23,
  BSE_MIDI_SIGNAL_CONTINUOUS_24 = Bse::MidiSignal::CONTINUOUS_24,
  BSE_MIDI_SIGNAL_CONTINUOUS_25 = Bse::MidiSignal::CONTINUOUS_25,
  BSE_MIDI_SIGNAL_CONTINUOUS_26 = Bse::MidiSignal::CONTINUOUS_26,
  BSE_MIDI_SIGNAL_CONTINUOUS_27 = Bse::MidiSignal::CONTINUOUS_27,
  BSE_MIDI_SIGNAL_CONTINUOUS_28 = Bse::MidiSignal::CONTINUOUS_28,
  BSE_MIDI_SIGNAL_CONTINUOUS_29 = Bse::MidiSignal::CONTINUOUS_29,
  BSE_MIDI_SIGNAL_CONTINUOUS_30 = Bse::MidiSignal::CONTINUOUS_30,
  BSE_MIDI_SIGNAL_CONTINUOUS_31 = Bse::MidiSignal::CONTINUOUS_31,
  BSE_MIDI_SIGNAL_CONSTANT_HIGH = Bse::MidiSignal::CONSTANT_HIGH,
  BSE_MIDI_SIGNAL_CONSTANT_CENTER = Bse::MidiSignal::CONSTANT_CENTER,
  BSE_MIDI_SIGNAL_CONSTANT_LOW = Bse::MidiSignal::CONSTANT_LOW,
  BSE_MIDI_SIGNAL_CONSTANT_NEGATIVE_CENTER = Bse::MidiSignal::CONSTANT_NEGATIVE_CENTER,
  BSE_MIDI_SIGNAL_CONSTANT_NEGATIVE_HIGH = Bse::MidiSignal::CONSTANT_NEGATIVE_HIGH,
  BSE_MIDI_SIGNAL_PARAMETER = Bse::MidiSignal::PARAMETER,
  BSE_MIDI_SIGNAL_NON_PARAMETER = Bse::MidiSignal::NON_PARAMETER,
  BSE_MIDI_SIGNAL_CONTROL_0 = Bse::MidiSignal::CONTROL_0,
  BSE_MIDI_SIGNAL_CONTROL_1 = Bse::MidiSignal::CONTROL_1,
  BSE_MIDI_SIGNAL_CONTROL_2 = Bse::MidiSignal::CONTROL_2,
  BSE_MIDI_SIGNAL_CONTROL_3 = Bse::MidiSignal::CONTROL_3,
  BSE_MIDI_SIGNAL_CONTROL_4 = Bse::MidiSignal::CONTROL_4,
  BSE_MIDI_SIGNAL_CONTROL_5 = Bse::MidiSignal::CONTROL_5,
  BSE_MIDI_SIGNAL_CONTROL_6 = Bse::MidiSignal::CONTROL_6,
  BSE_MIDI_SIGNAL_CONTROL_7 = Bse::MidiSignal::CONTROL_7,
  BSE_MIDI_SIGNAL_CONTROL_8 = Bse::MidiSignal::CONTROL_8,
  BSE_MIDI_SIGNAL_CONTROL_9 = Bse::MidiSignal::CONTROL_9,
  BSE_MIDI_SIGNAL_CONTROL_10 = Bse::MidiSignal::CONTROL_10,
  BSE_MIDI_SIGNAL_CONTROL_11 = Bse::MidiSignal::CONTROL_11,
  BSE_MIDI_SIGNAL_CONTROL_12 = Bse::MidiSignal::CONTROL_12,
  BSE_MIDI_SIGNAL_CONTROL_13 = Bse::MidiSignal::CONTROL_13,
  BSE_MIDI_SIGNAL_CONTROL_14 = Bse::MidiSignal::CONTROL_14,
  BSE_MIDI_SIGNAL_CONTROL_15 = Bse::MidiSignal::CONTROL_15,
  BSE_MIDI_SIGNAL_CONTROL_16 = Bse::MidiSignal::CONTROL_16,
  BSE_MIDI_SIGNAL_CONTROL_17 = Bse::MidiSignal::CONTROL_17,
  BSE_MIDI_SIGNAL_CONTROL_18 = Bse::MidiSignal::CONTROL_18,
  BSE_MIDI_SIGNAL_CONTROL_19 = Bse::MidiSignal::CONTROL_19,
  BSE_MIDI_SIGNAL_CONTROL_20 = Bse::MidiSignal::CONTROL_20,
  BSE_MIDI_SIGNAL_CONTROL_21 = Bse::MidiSignal::CONTROL_21,
  BSE_MIDI_SIGNAL_CONTROL_22 = Bse::MidiSignal::CONTROL_22,
  BSE_MIDI_SIGNAL_CONTROL_23 = Bse::MidiSignal::CONTROL_23,
  BSE_MIDI_SIGNAL_CONTROL_24 = Bse::MidiSignal::CONTROL_24,
  BSE_MIDI_SIGNAL_CONTROL_25 = Bse::MidiSignal::CONTROL_25,
  BSE_MIDI_SIGNAL_CONTROL_26 = Bse::MidiSignal::CONTROL_26,
  BSE_MIDI_SIGNAL_CONTROL_27 = Bse::MidiSignal::CONTROL_27,
  BSE_MIDI_SIGNAL_CONTROL_28 = Bse::MidiSignal::CONTROL_28,
  BSE_MIDI_SIGNAL_CONTROL_29 = Bse::MidiSignal::CONTROL_29,
  BSE_MIDI_SIGNAL_CONTROL_30 = Bse::MidiSignal::CONTROL_30,
  BSE_MIDI_SIGNAL_CONTROL_31 = Bse::MidiSignal::CONTROL_31,
  BSE_MIDI_SIGNAL_CONTROL_32 = Bse::MidiSignal::CONTROL_32,
  BSE_MIDI_SIGNAL_CONTROL_33 = Bse::MidiSignal::CONTROL_33,
  BSE_MIDI_SIGNAL_CONTROL_34 = Bse::MidiSignal::CONTROL_34,
  BSE_MIDI_SIGNAL_CONTROL_35 = Bse::MidiSignal::CONTROL_35,
  BSE_MIDI_SIGNAL_CONTROL_36 = Bse::MidiSignal::CONTROL_36,
  BSE_MIDI_SIGNAL_CONTROL_37 = Bse::MidiSignal::CONTROL_37,
  BSE_MIDI_SIGNAL_CONTROL_38 = Bse::MidiSignal::CONTROL_38,
  BSE_MIDI_SIGNAL_CONTROL_39 = Bse::MidiSignal::CONTROL_39,
  BSE_MIDI_SIGNAL_CONTROL_40 = Bse::MidiSignal::CONTROL_40,
  BSE_MIDI_SIGNAL_CONTROL_41 = Bse::MidiSignal::CONTROL_41,
  BSE_MIDI_SIGNAL_CONTROL_42 = Bse::MidiSignal::CONTROL_42,
  BSE_MIDI_SIGNAL_CONTROL_43 = Bse::MidiSignal::CONTROL_43,
  BSE_MIDI_SIGNAL_CONTROL_44 = Bse::MidiSignal::CONTROL_44,
  BSE_MIDI_SIGNAL_CONTROL_45 = Bse::MidiSignal::CONTROL_45,
  BSE_MIDI_SIGNAL_CONTROL_46 = Bse::MidiSignal::CONTROL_46,
  BSE_MIDI_SIGNAL_CONTROL_47 = Bse::MidiSignal::CONTROL_47,
  BSE_MIDI_SIGNAL_CONTROL_48 = Bse::MidiSignal::CONTROL_48,
  BSE_MIDI_SIGNAL_CONTROL_49 = Bse::MidiSignal::CONTROL_49,
  BSE_MIDI_SIGNAL_CONTROL_50 = Bse::MidiSignal::CONTROL_50,
  BSE_MIDI_SIGNAL_CONTROL_51 = Bse::MidiSignal::CONTROL_51,
  BSE_MIDI_SIGNAL_CONTROL_52 = Bse::MidiSignal::CONTROL_52,
  BSE_MIDI_SIGNAL_CONTROL_53 = Bse::MidiSignal::CONTROL_53,
  BSE_MIDI_SIGNAL_CONTROL_54 = Bse::MidiSignal::CONTROL_54,
  BSE_MIDI_SIGNAL_CONTROL_55 = Bse::MidiSignal::CONTROL_55,
  BSE_MIDI_SIGNAL_CONTROL_56 = Bse::MidiSignal::CONTROL_56,
  BSE_MIDI_SIGNAL_CONTROL_57 = Bse::MidiSignal::CONTROL_57,
  BSE_MIDI_SIGNAL_CONTROL_58 = Bse::MidiSignal::CONTROL_58,
  BSE_MIDI_SIGNAL_CONTROL_59 = Bse::MidiSignal::CONTROL_59,
  BSE_MIDI_SIGNAL_CONTROL_60 = Bse::MidiSignal::CONTROL_60,
  BSE_MIDI_SIGNAL_CONTROL_61 = Bse::MidiSignal::CONTROL_61,
  BSE_MIDI_SIGNAL_CONTROL_62 = Bse::MidiSignal::CONTROL_62,
  BSE_MIDI_SIGNAL_CONTROL_63 = Bse::MidiSignal::CONTROL_63,
  BSE_MIDI_SIGNAL_CONTROL_64 = Bse::MidiSignal::CONTROL_64,
  BSE_MIDI_SIGNAL_CONTROL_65 = Bse::MidiSignal::CONTROL_65,
  BSE_MIDI_SIGNAL_CONTROL_66 = Bse::MidiSignal::CONTROL_66,
  BSE_MIDI_SIGNAL_CONTROL_67 = Bse::MidiSignal::CONTROL_67,
  BSE_MIDI_SIGNAL_CONTROL_68 = Bse::MidiSignal::CONTROL_68,
  BSE_MIDI_SIGNAL_CONTROL_69 = Bse::MidiSignal::CONTROL_69,
  BSE_MIDI_SIGNAL_CONTROL_70 = Bse::MidiSignal::CONTROL_70,
  BSE_MIDI_SIGNAL_CONTROL_71 = Bse::MidiSignal::CONTROL_71,
  BSE_MIDI_SIGNAL_CONTROL_72 = Bse::MidiSignal::CONTROL_72,
  BSE_MIDI_SIGNAL_CONTROL_73 = Bse::MidiSignal::CONTROL_73,
  BSE_MIDI_SIGNAL_CONTROL_74 = Bse::MidiSignal::CONTROL_74,
  BSE_MIDI_SIGNAL_CONTROL_75 = Bse::MidiSignal::CONTROL_75,
  BSE_MIDI_SIGNAL_CONTROL_76 = Bse::MidiSignal::CONTROL_76,
  BSE_MIDI_SIGNAL_CONTROL_77 = Bse::MidiSignal::CONTROL_77,
  BSE_MIDI_SIGNAL_CONTROL_78 = Bse::MidiSignal::CONTROL_78,
  BSE_MIDI_SIGNAL_CONTROL_79 = Bse::MidiSignal::CONTROL_79,
  BSE_MIDI_SIGNAL_CONTROL_80 = Bse::MidiSignal::CONTROL_80,
  BSE_MIDI_SIGNAL_CONTROL_81 = Bse::MidiSignal::CONTROL_81,
  BSE_MIDI_SIGNAL_CONTROL_82 = Bse::MidiSignal::CONTROL_82,
  BSE_MIDI_SIGNAL_CONTROL_83 = Bse::MidiSignal::CONTROL_83,
  BSE_MIDI_SIGNAL_CONTROL_84 = Bse::MidiSignal::CONTROL_84,
  BSE_MIDI_SIGNAL_CONTROL_85 = Bse::MidiSignal::CONTROL_85,
  BSE_MIDI_SIGNAL_CONTROL_86 = Bse::MidiSignal::CONTROL_86,
  BSE_MIDI_SIGNAL_CONTROL_87 = Bse::MidiSignal::CONTROL_87,
  BSE_MIDI_SIGNAL_CONTROL_88 = Bse::MidiSignal::CONTROL_88,
  BSE_MIDI_SIGNAL_CONTROL_89 = Bse::MidiSignal::CONTROL_89,
  BSE_MIDI_SIGNAL_CONTROL_90 = Bse::MidiSignal::CONTROL_90,
  BSE_MIDI_SIGNAL_CONTROL_91 = Bse::MidiSignal::CONTROL_91,
  BSE_MIDI_SIGNAL_CONTROL_92 = Bse::MidiSignal::CONTROL_92,
  BSE_MIDI_SIGNAL_CONTROL_93 = Bse::MidiSignal::CONTROL_93,
  BSE_MIDI_SIGNAL_CONTROL_94 = Bse::MidiSignal::CONTROL_94,
  BSE_MIDI_SIGNAL_CONTROL_95 = Bse::MidiSignal::CONTROL_95,
  BSE_MIDI_SIGNAL_CONTROL_96 = Bse::MidiSignal::CONTROL_96,
  BSE_MIDI_SIGNAL_CONTROL_97 = Bse::MidiSignal::CONTROL_97,
  BSE_MIDI_SIGNAL_CONTROL_98 = Bse::MidiSignal::CONTROL_98,
  BSE_MIDI_SIGNAL_CONTROL_99 = Bse::MidiSignal::CONTROL_99,
  BSE_MIDI_SIGNAL_CONTROL_100 = Bse::MidiSignal::CONTROL_100,
  BSE_MIDI_SIGNAL_CONTROL_101 = Bse::MidiSignal::CONTROL_101,
  BSE_MIDI_SIGNAL_CONTROL_102 = Bse::MidiSignal::CONTROL_102,
  BSE_MIDI_SIGNAL_CONTROL_103 = Bse::MidiSignal::CONTROL_103,
  BSE_MIDI_SIGNAL_CONTROL_104 = Bse::MidiSignal::CONTROL_104,
  BSE_MIDI_SIGNAL_CONTROL_105 = Bse::MidiSignal::CONTROL_105,
  BSE_MIDI_SIGNAL_CONTROL_106 = Bse::MidiSignal::CONTROL_106,
  BSE_MIDI_SIGNAL_CONTROL_107 = Bse::MidiSignal::CONTROL_107,
  BSE_MIDI_SIGNAL_CONTROL_108 = Bse::MidiSignal::CONTROL_108,
  BSE_MIDI_SIGNAL_CONTROL_109 = Bse::MidiSignal::CONTROL_109,
  BSE_MIDI_SIGNAL_CONTROL_110 = Bse::MidiSignal::CONTROL_110,
  BSE_MIDI_SIGNAL_CONTROL_111 = Bse::MidiSignal::CONTROL_111,
  BSE_MIDI_SIGNAL_CONTROL_112 = Bse::MidiSignal::CONTROL_112,
  BSE_MIDI_SIGNAL_CONTROL_113 = Bse::MidiSignal::CONTROL_113,
  BSE_MIDI_SIGNAL_CONTROL_114 = Bse::MidiSignal::CONTROL_114,
  BSE_MIDI_SIGNAL_CONTROL_115 = Bse::MidiSignal::CONTROL_115,
  BSE_MIDI_SIGNAL_CONTROL_116 = Bse::MidiSignal::CONTROL_116,
  BSE_MIDI_SIGNAL_CONTROL_117 = Bse::MidiSignal::CONTROL_117,
  BSE_MIDI_SIGNAL_CONTROL_118 = Bse::MidiSignal::CONTROL_118,
  BSE_MIDI_SIGNAL_CONTROL_119 = Bse::MidiSignal::CONTROL_119,
  BSE_MIDI_SIGNAL_CONTROL_120 = Bse::MidiSignal::CONTROL_120,
  BSE_MIDI_SIGNAL_CONTROL_121 = Bse::MidiSignal::CONTROL_121,
  BSE_MIDI_SIGNAL_CONTROL_122 = Bse::MidiSignal::CONTROL_122,
  BSE_MIDI_SIGNAL_CONTROL_123 = Bse::MidiSignal::CONTROL_123,
  BSE_MIDI_SIGNAL_CONTROL_124 = Bse::MidiSignal::CONTROL_124,
  BSE_MIDI_SIGNAL_CONTROL_125 = Bse::MidiSignal::CONTROL_125,
  BSE_MIDI_SIGNAL_CONTROL_126 = Bse::MidiSignal::CONTROL_126,
  BSE_MIDI_SIGNAL_CONTROL_127 = Bse::MidiSignal::CONTROL_127,
} BseMidiSignalType;
#endif // BSE_IDL_SURROGATES


/* --- convenience functions --- */
const gchar*	bse_error_blurb			(Bse::ErrorType	 error_value);
Bse::ErrorType	bse_error_from_errno		(gint v_errno, Bse::ErrorType fallback);

#define bse_assert_ok(error)    G_STMT_START{                           \
     if G_UNLIKELY (error)                                              \
       {                                                                \
         g_log (G_LOG_DOMAIN, G_LOG_LEVEL_ERROR,                        \
                "%s:%d: unexpected error: %s",                          \
                __FILE__, __LINE__, bse_error_blurb (error));           \
       }                                                                \
}G_STMT_END

G_END_DECLS


#endif /* __BSE_ENUMS_H__ */
