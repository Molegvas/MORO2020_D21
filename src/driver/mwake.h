/*
 *
 *
 */

#ifndef _MWAKE_H_
#define _MWAKE_H_

#include "stdint.h"

#ifdef MWAKE

  class MWake
  {
    public:

      MWake();
      ~MWake();


      static constexpr uint8_t frame    = 0xFF; // Максимальная длина пакета 255 (полезных данных)


      void wakeInit( uint8_t addr, long time );
      void wakeRead();

      // передача ответа на команду
      void txReplay(char n, char err);
      void configReply(char n, char err, uint8_t comm);
  
      // работа с буфером приема
      uint16_t get16(int i);
      float getF16(int i);

      // работа с буфером передачи
      void setU8(int id, uint8_t value);

      void testReply( int n );                  // тест отправить n байт из буфера приемника

    private:

      void doCrc8(char b, char *crc);
      void wakeWrite();
      void wakeStartWrite();

    public:

      // Константы протокола
      // static constexpr uint8_t fend     = 0xC0; // Frame END
      // static constexpr uint8_t fesc     = 0xDB; // Frame ESCape
      // static constexpr uint8_t tfend    = 0xDC; // Transposed Frame END
      // static constexpr uint8_t tfesc    = 0xDD; // Transposed Frame ESCape
      // static constexpr uint8_t crc_init = 0xDE; // Initial CRC value
      //static constexpr uint8_t frame    = 0xFF; // Максимальная длина пакета 255 (полезных данных)

      // Коды универсальных команд:
      static constexpr uint8_t cmd_nop  = 0x00; // нет операции
      static constexpr uint8_t cmd_err  = 0x01; // ошибка приема пакета
      static constexpr uint8_t cmd_echo = 0x02; // передать эхо
      static constexpr uint8_t cmd_info = 0x03; // передать информацию об устройстве

      //static uint8_t txNbt;          // количество байт данных в пакете
      //static uint8_t command;        // код команды на выполнение
      //static char    txDat[frame];   // массив данных для передачи

    private:
      // Константы протокола
      //static constexpr uint8_t fend     = 0xC0; // Frame END
      //static constexpr uint8_t fesc     = 0xDB; // Frame ESCape
      //static constexpr uint8_t tfend    = 0xDC; // Transposed Frame END
      //static constexpr uint8_t tfesc    = 0xDD; // Transposed Frame ESCape
      //static constexpr uint8_t crc_init = 0xDE; // Initial CRC value
      //static constexpr uint8_t frame    = 0xFF; // Максимальная длина пакета 255 (полезных данных)

      //static char    rxNbt;          // принятое количество байт в пакете
      //static char    rxDat[frame];   // массив принятых данных
      //static char    txCmd;          // команда, передаваемая в пакете

  };

#else

  // Константы протокола
  static constexpr uint8_t fend     = 0xC0; // Frame END
  static constexpr uint8_t fesc     = 0xDB; // Frame ESCape
  static constexpr uint8_t tfend    = 0xDC; // Transposed Frame END
  static constexpr uint8_t tfesc    = 0xDD; // Transposed Frame ESCape
  static constexpr uint8_t crc_init = 0xDE; // Initial CRC value
  static constexpr uint8_t frame    = 0xFF; // Максимальная длина пакета 255 (полезных данных)

  // Коды ошибок:
  static constexpr uint8_t err_no   = 0x00; // no error
  static constexpr uint8_t err_tx   = 0x01; // Rx/Tx error
  static constexpr uint8_t err_bu   = 0x02; // device busy error
  static constexpr uint8_t err_re   = 0x03; // device not ready error
  static constexpr uint8_t err_pa   = 0x04; // parameters value error
  static constexpr uint8_t err_nr   = 0x05; // no replay
  static constexpr uint8_t err_nc   = 0x06; // no carrier

    // Коды универсальных команд:
  static constexpr uint8_t cmd_nop  = 0x00; // нет операции
  static constexpr uint8_t cmd_err  = 0x01; // ошибка приема пакета
  static constexpr uint8_t cmd_echo = 0x02; // передать эхо
  static constexpr uint8_t cmd_info = 0x03; // передать информацию об устройстве

  void wakeInit( uint8_t addr, long time );
  void wakeRead();
  void txReplay(char n, char err);          // передача ответа на команду

  uint16_t get16(int i);
  float getF16(int i);
  void testReply( int n );                  // тест отправить n байт из буфера приемника

#endif

#endif  //!_MWAKE_H_
