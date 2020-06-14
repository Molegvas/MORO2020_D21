#ifndef _MCOMMANDS_H_
#define _MCOMMANDS_H_
/*


*/

#include "stdint.h"

class MBoard;
class MWake;

class MCommands
{
  public:

  MCommands(MBoard * board);
  ~MCommands();
  
  
  void doCommand();

  void readUI();
  
  void writeMult();
  bool writeKp(uint8_t role, float value);
  bool writeKi(uint8_t role, float value);
  bool writeKd(uint8_t role, float value);
  bool writeHz(uint8_t role, float value);
  bool writeBitsSign(uint8_t role, uint8_t bits, uint8_t sign);
  bool writeOutputRange(uint8_t role, int16_t min, int16_t max);

  private:

  MBoard * Board;
  MWake * Wake = nullptr;

  public:

    // #define INTEG_MAX    (INT32_MAX)
    // #define INTEG_MIN    (INT32_MIN)
    // #define DERIV_MAX    (INT16_MAX)
    // #define DERIV_MIN    (INT16_MIN)

    // #define PARAM_SHIFT  8
    // #define PARAM_BITS   16
    // #define PARAM_MAX    (((0x1ULL << PARAM_BITS)-1) >> PARAM_SHIFT) 
    // #define PARAM_MULT   (((0x1ULL << PARAM_BITS)) >> (PARAM_BITS - PARAM_SHIFT)) 

    enum NAME
    {
      KP = 0,   // 
      KI,       // 
      KD,       // 
      HZ,       // резерв, всегда 10
      BITS,     // резерв, всегда 16
      SIGN,     // 
      OUT_L,    // 
      OUT_H     //  
    };

    enum ROLES
    {
      RS = 0,    // режим прямого регулирования
      RU,        // режим управления напряжением
      RI,        // режим управления током
      RD         // режим управления током разряда
    };

  
  private:

    static constexpr uint8_t param_shift =  8;
    static constexpr uint8_t param_bits  = 16;
    static constexpr uint16_t param_max  = (((0x1 << param_bits)-1) >> param_shift); 
    static constexpr uint16_t param_mult = (((0x1 << param_bits)) >> (param_bits - param_shift));


    uint32_t floatToParam(float in);
    void     txU08(uint8_t id,  uint8_t value);
    void     txU16(uint8_t id, uint16_t value);
    void     txU32(uint8_t id, uint32_t value);


};

#endif  //!_MCOMMANDS_H_
