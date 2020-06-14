/*


*/

#include "mcommands.h"
//#include "adc_commands.h"
//#include "pid_commands.h"
#include "board/mpins.h"
#include "board/mboard.h"
//#include "power/power_reg.h"
#include "driver/mwake.h"
#include "stdint.h"
#include <Arduino.h>


MCommands::MCommands(MBoard * board) : Board(board)
{
  Wake = new MWake();

  Wake->wakeInit( 0x00, 50 );   // Адрес в сети и время ожидания ответа

}

MCommands::~MCommands()
{
  delete Wake;
}

    const uint8_t cmd_read_u_i          = 0x10;

    // Команды настройки ПИД-регулятора
    const uint8_t cmd_write_mult        = 0x20;
    const uint8_t cmd_write_kp          = 0x21;
    const uint8_t cmd_write_ki          = 0x22;
    const uint8_t cmd_write_kd          = 0x23;
    const uint8_t cmd_write_hz          = 0x24;
    const uint8_t cmd_write_bits_sign   = 0x25;
//  const uint8_t cmd_write_sign    = 0x26;   // reserved

    // Команды управления ПИД-регулятором

    const uint8_t cmd_write_range       = 0x28;
// const uint8_t cmd_pid_configure        = 0x40; // kp, ki, kd, hz, bits, sign 
// const uint8_t cmd_pid_coefficients     = 0x41; // kp, ki, kd, hz 
// const uint8_t cmd_pid_output_range     = 0x42; // min, max
// const uint8_t cmd_pid_output_config    = 0x43; // bits, sign
// const uint8_t cmd_pid_clear            = 0x44; 

// const uint8_t cmd_pid_stop_go          = 0x45; // стоп-пауза-пуск 
// const uint8_t cmd_pid_test             = 0x46; // mode, setpoint, min, max


// Имя устройства
static constexpr char Info[] = {"Q920up Rev0.0\n\0"};   //

//   // state1
// bool _switchStatus          = true;  // коммутатор ( foff_pin 21 D21 PA23 )
// bool _converterStatus       = false;  // преобразователь
// bool _currentControlStatus  = false;  // регулирование по току
// bool _voltageControlStatus  = false;  // регулирование по напряжению
// bool _chargeStatus          = false;  // заряд
// bool _dischargeStatus       = false;  // разряд
// bool _pauseStatus           = false;  // пауза
// bool _reserve1Status        = false;  // резерв 1

//   // state2
// bool _overHeatingStatus     = false;  // перегрев
// bool _overloadStatus        = false;  // перегрузка
// bool _powerLimitationStatus = false;  // ограничение мощности
// bool _reversePolarityStatus = false;  // обратная полярность
// bool _shortCircuitStatus    = false;  // короткое замыкание
// bool _calibrationStatus     = false;  // калибровка
// bool _upgradeStatus         = false;  // обновление
// bool _reserve2Status        = false;  // резерв 2

      // 




//     // АЦП - настройки
// static constexpr uint8_t cmd_adc_read_probes          = 0x50; // Read all probes
// static constexpr uint8_t cmd_adc_config               = 0x51; // параметры измерителя
// static constexpr uint8_t cmd_adc_config52             = 0x52; // параметры АЦП
// static constexpr uint8_t cmd_adc_ref_compensation     = 0x53; // reference buffer offset compensation
// static constexpr uint8_t cmd_adc_read_mv              = 0x54; // Read probes, mV
// static constexpr uint8_t cmd_set_adc_bat              = 0x55;
// static constexpr uint8_t cmd_set_adc_shunt            = 0x56;
// static constexpr uint8_t cmd_set_adc_rtu              = 0x57;
// static constexpr uint8_t cmd_offset_compensation      = 0x58;
// static constexpr uint8_t cmd_offset_gain_compensation = 0x59;

//         // Команды управления процессами
// static constexpr uint8_t cmd_switch_foff              = 0x60; // foff_pin 21  D21 PA23
// static constexpr uint8_t cmd_converter_off            = 0x61; // off_pin   2  D4  PA14



//     // ЦАП - настройки
//     // https://stackoverflow.com/questions/53542591/using-external-vref-for-samd21-dac
// enum dac_reference 
// {
//     /** 1V from the internal band-gap reference*/
//     DAC_REFERENCE_INT1V = DAC_CTRLB_REFSEL(0),
//     /** Analog V<SUB>CC</SUB> as reference */
//     DAC_REFERENCE_AVCC  = DAC_CTRLB_REFSEL(1),
//     /** External reference on AREF */
//     DAC_REFERENCE_AREF  = DAC_CTRLB_REFSEL(2),
// };

    // Переменные - уточнить типы  
//extern char     rxNbt;          //+ принятое количество байт в пакете
//extern char     rxDat[MWake::frame];   //+ массив принятых данных
//extern uint8_t  command;        // код команды на выполнение

//extern char     TxCmd;          // команда, передаваемая в пакете
//extern char     txNbt;          // количество байт данных в пакете
//extern char     txDat[MWake::frame];   //+ массив данных для передачи

//extern float voltage;

uint8_t cmd = MWake::cmd_nop;

uint8_t state1 = 0b00000000;
uint8_t state2 = 0b00000000;


//void doInfo();
//void doEcho();
//void doErr();


void MCommands::doCommand()
{
  //cmd = command;
  //cmd = cmd_read_u_i;         // 0x10   test
  //cmd = cmd_write_mult;  // 0x20   test
  //cmd = cmd_write_kp;         // 0x21   test
  //cmd = cmd_write_ki;         // 0x22   test
  //cmd = cmd_write_kd;         // 0x23   test
  //cmd = cmd_write_hz;         // 0x24   test
  cmd = cmd_write_bits_sign;    // 0x25   test

  if( cmd != MWake::cmd_nop)
  {
    #ifdef DEBUG_COMMANDS
      Serial.print(" command -> 0x"); Serial.println(cmd, HEX);
    #endif

    switch( cmd )
    {
      //Команды управления процессами
      case cmd_read_u_i :     // 0x10; cmd_read_u_i
      
        Serial2.print("Uu");   // test

        //   txNbt = 5;
        //   txReplay( txNbt, 0x00 ); 

  
          Board->calcVoltage( 3333 );  // test
          Board->calcCurrent( 2222 );  // test
        break;

      case cmd_write_mult :           // 0x20
        writeMult();                  // test
        break;

      case cmd_write_kp :             // 0x21
        writeKp( RU, 0.5 );           // test
        break;

      case cmd_write_ki :             // 0x22
        writeKi( RI, 1.0 );           // test
        break;

      case cmd_write_kd :             // 0x23
        writeKd( RD, 1.0 );           // test
        break;

      case cmd_write_hz :             // 0x24
        writeHz( RS, 10.0 );          // test
        break;

      case cmd_write_bits_sign :      // 0x25;
        writeBitsSign( RS, 16, 1 );   // test
        break;

  //     //   // Команды работы с измерителями
  //     // case cmd_adc_read_probes:           doReadProbes();             break;  // 0x50
  //     // case cmd_adc_config:                doAdcConfig();              break;  // 0x51
  //     // case cmd_adc_config52:              doAdcConfig52();            break;  // 0x52
  //     // case cmd_adc_ref_compensation:      doAdcRefCompensation();     break;  // 0x53
  //     // case cmd_adc_read_mv:               doReadValues();             break;  // 0x54
  //     // case cmd_set_adc_bat:               doAdcBat();                 break;  // 0x55
  //     // case cmd_set_adc_shunt:             doAdcShunt();               break;  // 0x56
  //     // case cmd_set_adc_rtu:               doAdcRtu();                 break;  // 0x57
  //     // case cmd_offset_compensation:       doOffsetCompensation();     break;  // 0x58
  //     // case cmd_offset_gain_compensation:  doOffsetGainCompensation(); break;  // 0x59
  //     // //case cmd_:                        do();                       break;  // 0x5a

  //     //   // Команды работы с регуляторами
  //     // case cmd_pid_configure:             doPidConfigure();           break;  // 0x40
  //     // case cmd_pid_coefficients:          doPidCoefficients();        break;  // 0x41
  //     // case cmd_pid_output_range:          doPidOutputRange();         break;  // 0x42
  //     // case cmd_pid_output_config:         doPidOutputConfig();        break;  // 0x43
  //     // case cmd_pid_clear:                 doPidClear();               break;  // 0x44
  //     // case cmd_pid_test:                  doPidTest();                break;  // 0x46

  //     //   // Команды управления
  //     // //case cmd_:                        do();                       break;  // 0x20


  //       // Команды универсальные
  //     case cmd_err:                       doErr();                    break;  // 0x01
  //     case cmd_echo:                      doEcho();                   break;  // 0x02
  //     case cmd_info:                      doInfo();                   break;  // 0x03

      default: 
      ;
    }
    cmd = MWake::cmd_nop;
  }
}

// // передать информацию об устройстве
// void doInfo()
// {
//   char ch = 1;
//   int i = 0;

//   for( i = 0; i < frame && ch; i++ )
//   {
//   ch = txDat[i] = Info[i];

//   #ifdef DEBUG_WAKE
//     Serial.print( ch );
//   #endif
//   }
  
//   txReplay( i, txDat[0] );        // Искусственный прием, об ошибках не сообщается
// }

// // передать эхо
// void doEcho()
// {
//   for( int i = 0; i < rxNbt && i < frame; i++ )
//   txDat[i] = rxDat[i];
//   txReplay( rxNbt, txDat[0] );
//   #ifdef DEBUG_WAKE
//     Serial.print("команда эхо = "); Serial.print( rxNbt );
//   #endif
// }

// // ошибка приема пакета
// void doErr()
// {
//   txReplay(1, err_tx);
//   #ifdef DEBUG_WAKE
//     Serial.println("обработка ошибки");
//   #endif
// }

// // Формирование регистра состояния 1
// void doState1()
// {
//   _switchStatus         ? state1 |= 0b10000000 : state1 &= 0b01111111; 
//   _converterStatus      ? state1 |= 0b01000000 : state1 &= 0b10111111; 
//   _currentControlStatus ? state1 |= 0b00100000 : state1 &= 0b11011111; 
//   _voltageControlStatus ? state1 |= 0b00010000 : state1 &= 0b11101111; 
//   _chargeStatus         ? state1 |= 0b00001000 : state1 &= 0b11110111; 
//   _dischargeStatus      ? state1 |= 0b00000100 : state1 &= 0b11111011; 
//   _pauseStatus          ? state1 |= 0b00000010 : state1 &= 0b11111101; 
//   _reserve1Status       ? state1 |= 0b00000001 : state1 &= 0b11111110;

//   switchFoff(_switchStatus);        // Непрерывное подтверждение состояния
//   converterOff(_converterStatus);
// }

// // Формирование регистра состояния 2 
// void doState2()
// {
//   _overHeatingStatus     ? state2 |= 0b10000000 : state2 &= 0b01111111; 
//   _overloadStatus        ? state2 |= 0b01000000 : state2 &= 0b10111111; 
//   _powerLimitationStatus ? state2 |= 0b00100000 : state2 &= 0b11011111; 
//   _reversePolarityStatus ? state2 |= 0b00010000 : state2 &= 0b11101111; 
//   _shortCircuitStatus    ? state2 |= 0b00001000 : state2 &= 0b11110111; 
//   _calibrationStatus     ? state2 |= 0b00000100 : state2 &= 0b11111011; 
//   _upgradeStatus         ? state2 |= 0b00000010 : state2 &= 0b11111101; 
//   _reserve2Status        ? state2 |= 0b00000001 : state2 &= 0b11111110; 
// }

constexpr float hz = 10.0;    // Пока без вариантов

bool _cfg_err;    // Этого не будет - проверки на стороне ESP минимальны

// На стороне ESP все float параметры преобразуются в целочисленные 
//                                                    НЕ ПРОВЕРЕНО
uint32_t MCommands::floatToParam(float in)
{
  if (in > param_max || in < 0)
  {
    _cfg_err = true;
    return 0;
  }

  uint32_t param = in * param_mult;

  if (in != 0 && param == 0) {
    _cfg_err = true;
    return 0;
  }
  
  return param;
}

// Запись байта в буфер передатчика по индексу 
void MCommands::txU08(uint8_t id,  uint8_t value)
{
  Wake->setU8( id, value );
}

// Запись двухбайтового числа в буфер передатчика по индексу 
void MCommands::txU16(uint8_t id, uint16_t value)
{
  Wake->setU8( id,   uint8_t(( value >>  8 ) & 0xff ));
  Wake->setU8( id+1, uint8_t(  value         & 0xff ));
}

// Запись четырехбайтового числа в буфер передатчика по индексу 
void MCommands::txU32(uint8_t id, uint32_t value)
{
  Wake->setU8( id,   uint8_t(( value >> 24 ) & 0xff ));
  Wake->setU8( id+1, uint8_t(( value >> 16 ) & 0xff ));
  Wake->setU8( id+2, uint8_t(( value >>  8 ) & 0xff ));
  Wake->setU8( id+3, uint8_t(  value         & 0xff ));
}

// Команда запроса данных измерений драйвером напряжения и тока
// Ожидаемый ответ: целочисленные знаковые в милливольтах и миллиамперах
// соответственно, и два байта состояний.
void MCommands::readUI()
{        
  Wake->configReply( 1, 0, cmd_read_u_i);    // txNbt, err, command
}

// Запись копии настроек в драйвер. Необходима синхронизация коэффициентов
// преобразования на передающей и приемной (драйвер) стороне.
// Ожидаемый ответ: только подтверждение
void MCommands::writeMult()
{
  txU08( 1, param_shift );
  txU08( 2, param_bits  );
  txU16( 3, param_max   );
  txU16( 5, param_mult  );
                // txNbt, err, command
  Wake->configReply( 7, 0, cmd_write_mult);
}

// Преобразование и запись в буфер передатчика целочисленного Kp
// и инициализация передачи. Если данные некорректны, будет 
// передано нулевое значение - пока так.
// Ожидаемый ответ: только подтверждение
bool MCommands::writeKp(uint8_t role, float value)
{
  txU08( 1, KP );
  txU08( 2, role & 0x03 );
  txU32( 3, floatToParam( value ) );
  Wake->configReply( 7, 0, cmd_write_kp);  // txNbt, err, command
  return true;
}

// Преобразование и запись в буфер передатчика целочисленного Ki
// и инициализация передачи. Если данные некорректны, будет 
// передано нулевое значение - пока так.
// Ожидаемый ответ: только подтверждение
bool MCommands::writeKi(uint8_t role, float value)
{
  txU08( 1, KI );
  txU08( 2, role & 0x03 );
  txU32( 3, floatToParam( value / hz ) );
  Wake->configReply( 7, 0, cmd_write_ki);  // txNbt, err, command
  return true;
}

// Преобразование и запись в буфер передатчика целочисленного Kd
// и инициализация передачи. Если данные некорректны, будет 
// передано нулевое значение - пока так.
// Если данные не корректны, изменения произведены не будут, 
// возвращается флаг ошибки (false).
// Ожидаемый ответ: только подтверждение
bool MCommands::writeKd(uint8_t role, float value)
{
  txU08( 1, KD );
  txU08( 2, role & 0x03 );
  txU32( 3, floatToParam( value * hz ) );
  Wake->configReply( 7, 0, cmd_write_kd);  // txNbt, err, command
  return true;
}

// Преобразование и запись в буфер передатчика целочисленного Hz
// и инициализация передачи. Если данные некорректны, будет 
// передано нулевое значение - пока так. 
// Эта функция резервная - пока частота всегда 10 Гц
// Ожидаемый ответ: только подтверждение
bool MCommands::writeHz(uint8_t role, float value)
{
  txU08( 1, HZ );
  txU08( 2, role & 0x03 );
  txU32( 3, floatToParam( value ) );
  Wake->configReply( 7, 0, cmd_write_hz);  // txNbt, err, command
  return true;
}

// Простейшая проверка при передаче, пересчет на стороне драйвера,
// отдельной команды для знака нет, так как обработка этих двух
// параметров совместная.
// Если данные не корректны, изменения произведены не будут, 
// возвращается флаг ошибки (false).
// Ожидаемый ответ: только подтверждение
bool MCommands::writeBitsSign(uint8_t role, uint8_t bits, uint8_t sign)
{
  if (bits > 16 || bits < 1 || sign > 1 || sign < 0) { return false; }
  txU08( 1, BITS );
  txU08( 2, role & 0x03 );
  txU08( 3, bits );
  txU08( 4, sign );
  Wake->configReply( 5, 0, cmd_write_bits_sign);  // txNbt, err, command
  return true;
}


// =============== Команды управления ПИД-регулятором ===============

// Изменение диапазона выходного напряжения ЦАП. 
// Если данные не корректны, изменения произведены не будут, 
// возвращается флаг ошибки (false).
// Ожидаемый ответ: только подтверждение
bool MCommands::writeOutputRange(uint8_t role, int16_t min, int16_t max)
{
  if (min >= max) { return false; }   // Не полная проверка
  txU08( 1, OUT_L );
  txU08( 2, role & 0x03 );
  txU16( 3, min );
  txU16( 5, max );
  Wake->configReply( 6, 0, cmd_write_range);  // txNbt, err, command
  return true;
}
