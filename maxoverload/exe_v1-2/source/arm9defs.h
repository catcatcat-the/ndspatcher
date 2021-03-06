// Subroutine function signatures
u32 compressionSignature[2]   = {0xDEC00621, 0x2106C0DE};
u32 a9cardReadSignature[2]    = {0x04100010, 0x040001A4};
u16 cardReadStartSignature[1] = {0xE92D};
u32 a9cardIdSignature[2]      = {0x040001A4,0x04100010};
u16 cardIdStartSignature[1]   = {0xE92D};
u32 a9instructionBHI[1]       = {0x8A000001};

u32 arm9ramAddrMod = 0;

/*
 * Note; the following hardcoded values have been recorded in original format
 * on this page: http://pastebin.com/zePzLeVL
 * on which, they can simple by posted in ODA for analysis
 *
 * TODO: better names for these sections, please...
 */
 u8 unk_42486C[0x1C0] = {
    0x3E,0x00,0x00,0xEA,0x0F,0x00,0xA0,0xE1,
    0x1E,0xFF,0x2F,0xE1,0x00,0x3E,0x00,0x02,
    0x58,0x02,0x0A,0x02,0x5C,0x02,0x0A,0x02,
    0x60,0x02,0x0A,0x02,0x18,0x20,0x9F,0xE5,
    0xB0,0x30,0xD2,0xE1,0x40,0x00,0x13,0xE3,
    0xFB,0xFF,0xFF,0x0A,0xB0,0x30,0xD2,0xE1,
    0x80,0x00,0x13,0xE3,0xF8,0xFF,0xFF,0x1A,
    0x1E,0xFF,0x2F,0xE1,0x00,0x00,0x0E,0x08,
    0x70,0x40,0x2D,0xE9,0xA4,0x30,0x9F,0xE5,
    0xA4,0x20,0x9F,0xE5,0x00,0x30,0x93,0xE5,
    0xB0,0xC0,0xD2,0xE1,0x03,0x40,0x80,0xE0,
    0x98,0x30,0x9F,0xE5,0x01,0x50,0xA0,0xE1,
    0xB0,0x30,0xC2,0xE1,0x0C,0x60,0xA0,0xE1,
    0xEB,0xFF,0xFF,0xEB,0x88,0x30,0x9F,0xE5,
    0x04,0x28,0xA0,0xE1,0x01,0xC0,0xA0,0xE3,
    0xB0,0xC0,0xC3,0xE1,0x04,0x14,0xA0,0xE1,
    0x22,0x28,0xA0,0xE1,0x02,0x38,0x83,0xE2,
    0xB0,0x20,0xC3,0xE1,0x24,0x0C,0xA0,0xE1,
    0x21,0x18,0xA0,0xE1,0x02,0x38,0x83,0xE2,
    0xB0,0x10,0xC3,0xE1,0x0F,0x00,0x00,0xE2,
    0x02,0x38,0x83,0xE2,0x24,0x48,0xA0,0xE1,
    0xB0,0x40,0xC3,0xE1,0xE0,0x00,0x80,0xE3,
    0x02,0x38,0x83,0xE2,0xB0,0x00,0xC3,0xE1,
    0x20,0x20,0xA0,0xE3,0x02,0x38,0x83,0xE2,
    0xB0,0x20,0xC3,0xE1,0xD4,0xFF,0xFF,0xEB,
    0x01,0x2C,0xA0,0xE3,0x02,0x33,0xA0,0xE3,
    0xB0,0x30,0xD3,0xE1,0x01,0x20,0x52,0xE2,
    0xB2,0x30,0xC5,0xE0,0xFA,0xFF,0xFF,0x1A,
    0x0C,0x30,0x9F,0xE5,0xB0,0x60,0xC3,0xE1,
    0x70,0x40,0xBD,0xE8,0x1E,0xFF,0x2F,0xE1,
    0xF0,0xFD,0x7F,0x02,0x04,0x02,0x00,0x04,
    0x08,0x40,0x00,0x00,0x00,0x00,0x04,0x08,
    0xF0,0x41,0x2D,0xE9,0xBE,0xFF,0xFF,0xEB,
    0x0C,0x30,0x90,0xE5,0x04,0x10,0x90,0xE5,
    0x00,0x50,0x93,0xE5,0x00,0x60,0x91,0xE5,
    0x08,0x30,0x90,0xE5,0x05,0x20,0x86,0xE0,
    0x00,0x80,0x93,0xE5,0x00,0x70,0x90,0xE5,
    0x00,0x20,0x81,0xE5,0x08,0x20,0x90,0xE5,
    0x05,0x30,0x88,0xE0,0x00,0x30,0x82,0xE5,
    0x0C,0x20,0x90,0xE5,0x00,0x30,0xA0,0xE3,
    0x00,0x30,0x82,0xE5,0x19,0x00,0x00,0xEA,
    0x04,0x30,0x17,0xE5,0xA6,0x44,0xA0,0xE1,
    0x04,0x00,0x53,0xE1,0x03,0x00,0x00,0x0A,
    0x04,0x00,0xA0,0xE1,0x07,0x10,0xA0,0xE1,
    0xB6,0xFF,0xFF,0xEB,0x04,0x40,0x07,0xE5,
    0x86,0x3B,0xA0,0xE1,0xA3,0x3B,0xA0,0xE1,
    0x02,0x2C,0x63,0xE2,0x02,0x00,0x55,0xE1,
    0x05,0x10,0xA0,0x31,0x02,0x10,0xA0,0x21,
    0x00,0x00,0xA0,0xE3,0x03,0x20,0x87,0xE0,
    0x02,0x00,0x00,0xEA,0x01,0x30,0x52,0xE5,
    0x08,0x30,0xC0,0xE7,0x01,0x00,0x80,0xE2,
    0x01,0x00,0x50,0xE1,0x01,0x20,0x82,0xE2,
    0xF9,0xFF,0xFF,0x3A,0x00,0x80,0x88,0xE0,
    0x05,0x50,0x61,0xE0,0x01,0x60,0x86,0xE0,
    0x00,0x00,0x55,0xE3,0xE3,0xFF,0xFF,0x1A,
    0xF0,0x41,0xBD,0xE8,0x1E,0xFF,0x2F,0xE1
};

u8 unk_424A2C[0x1AC] = {
    0x3E,0x00,0x00,0xEA,0x0F,0x00,0xA0,0xE1,
    0x1E,0xFF,0x2F,0xE1,0xD1,0x5E,0xA5,0xE0,
    0xD1,0x5E,0xA5,0xE0,0xD1,0x5E,0xA5,0xE0,
    0xD1,0x5E,0xA5,0xE0,0x18,0x20,0x9F,0xE5,
    0xB0,0x30,0xD2,0xE1,0x40,0x00,0x13,0xE3,
    0xFB,0xFF,0xFF,0x0A,0xB0,0x30,0xD2,0xE1,
    0x80,0x00,0x13,0xE3,0xF8,0xFF,0xFF,0x1A,
    0x1E,0xFF,0x2F,0xE1,0x00,0x00,0x0E,0x08,
    0x70,0x40,0x2D,0xE9,0xA4,0x30,0x9F,0xE5,
    0xA4,0x20,0x9F,0xE5,0x00,0x30,0x93,0xE5,
    0xB0,0xC0,0xD2,0xE1,0x03,0x40,0x80,0xE0,
    0x98,0x30,0x9F,0xE5,0x01,0x50,0xA0,0xE1,
    0xB0,0x30,0xC2,0xE1,0x0C,0x60,0xA0,0xE1,
    0xEB,0xFF,0xFF,0xEB,0x88,0x30,0x9F,0xE5,
    0x04,0x28,0xA0,0xE1,0x01,0xC0,0xA0,0xE3,
    0xB0,0xC0,0xC3,0xE1,0x04,0x14,0xA0,0xE1,
    0x22,0x28,0xA0,0xE1,0x02,0x38,0x83,0xE2,
    0xB0,0x20,0xC3,0xE1,0x24,0x0C,0xA0,0xE1,
    0x21,0x18,0xA0,0xE1,0x02,0x38,0x83,0xE2,
    0xB0,0x10,0xC3,0xE1,0x0F,0x00,0x00,0xE2,
    0x02,0x38,0x83,0xE2,0x24,0x48,0xA0,0xE1,
    0xB0,0x40,0xC3,0xE1,0xE0,0x00,0x80,0xE3,
    0x02,0x38,0x83,0xE2,0xB0,0x00,0xC3,0xE1,
    0x20,0x20,0xA0,0xE3,0x02,0x38,0x83,0xE2,
    0xB0,0x20,0xC3,0xE1,0xD4,0xFF,0xFF,0xEB,
    0x01,0x2C,0xA0,0xE3,0x02,0x33,0xA0,0xE3,
    0xB0,0x30,0xD3,0xE1,0x01,0x20,0x52,0xE2,
    0xB2,0x30,0xC5,0xE0,0xFA,0xFF,0xFF,0x1A,
    0x0C,0x30,0x9F,0xE5,0xB0,0x60,0xC3,0xE1,
    0x70,0x40,0xBD,0xE8,0x1E,0xFF,0x2F,0xE1,
    0xF0,0xFD,0x7F,0x02,0x04,0x02,0x00,0x04,
    0x08,0x40,0x00,0x00,0x00,0x00,0x04,0x08,
    0xF0,0x40,0x2D,0xE9,0x02,0xDC,0x4D,0xE2,
    0xBD,0xFF,0xFF,0xEB,0x0C,0x30,0x90,0xE5,
    0x04,0x10,0x90,0xE5,0x00,0x50,0x93,0xE5,
    0x00,0x60,0x91,0xE5,0x08,0x30,0x90,0xE5,
    0x05,0x20,0x86,0xE0,0x00,0x70,0x93,0xE5,
    0x00,0x20,0x81,0xE5,0x08,0x20,0x90,0xE5,
    0x05,0x30,0x87,0xE0,0x00,0x30,0x82,0xE5,
    0x0C,0x20,0x90,0xE5,0x00,0x30,0xA0,0xE3,
    0x00,0x30,0x82,0xE5,0x13,0x00,0x00,0xEA,
    0x0D,0x10,0xA0,0xE1,0xA6,0x04,0xA0,0xE1,
    0xBA,0xFF,0xFF,0xEB,0x86,0x3B,0xA0,0xE1,
    0xA3,0x3B,0xA0,0xE1,0x02,0x2C,0x63,0xE2,
    0x02,0x00,0x55,0xE1,0x05,0x20,0xA0,0x31,
    0x03,0x40,0x8D,0xE0,0x00,0x10,0xA0,0xE3,
    0x02,0x00,0x00,0xEA,0x01,0x30,0x54,0xE5,
    0x07,0x30,0xC1,0xE7,0x01,0x10,0x81,0xE2,
    0x02,0x00,0x51,0xE1,0x01,0x40,0x84,0xE2,
    0xF9,0xFF,0xFF,0x3A,0x01,0x70,0x87,0xE0,
    0x05,0x50,0x62,0xE0,0x02,0x60,0x86,0xE0,
    0x00,0x00,0x55,0xE3,0xE9,0xFF,0xFF,0x1A,
    0x02,0xDC,0x8D,0xE2,0xF0,0x40,0xBD,0xE8,
    0x1E,0xFF,0x2F,0xE1
};

const u8 unk_424BD8[0x10] = {
    0x04,0x00,0x9F,0xE5,0x00,0x00,0x90,0xE5,
    0x1E,0xFF,0x2F,0xE1,0x00,0xF8,0x7F,0x02
};

const u8 unk_424BE8[0x04] = {
    0x16,0x00,0x00,0xEA
};
