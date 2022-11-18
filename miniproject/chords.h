
#define NOTE_E2   40
#define NOTE_F2   41
#define NOTE_Fs2  42
#define NOTE_G2   43
#define NOTE_Gs2 44
#define NOTE_A2  45
#define NOTE_As2 46
#define NOTE_B2  47
#define NOTE_C3  48
#define NOTE_Cs3 49
#define NOTE_D3  50
#define NOTE_Ds3 51
#define NOTE_E3  52
#define NOTE_F3  53
#define NOTE_Fs3 54
#define NOTE_G3  55
#define NOTE_Gs3 56
#define NOTE_A3  57
#define NOTE_As3 58
#define NOTE_B3  59
#define NOTE_C4  60
#define NOTE_Cs4 61
#define NOTE_D4  62
#define NOTE_Ds4 63
#define NOTE_E4  64
#define NOTE_F4  65
#define NOTE_Fs4 66
#define NOTE_G4  67
#define NOTE_Gs4 68
#define NOTE_A4  69
#define NOTE_As4 70
#define NOTE_B4  71

// The equation for note to frequency is:
// float freq = 440.0f * exp2f((float)(note - 69) * 0.0833333f);

// according to http://www.guitar-chords.org.uk/
// and http://www.8notes.com/guitar_chord_chart/c.asp
//
              // open =  NOTE_E2  NOTE_A2  NOTE_D3  NOTE_G3  NOTE_B3  NOTE_E4
int Cmajor[6] = {      0, NOTE_C3, NOTE_E3, NOTE_G3, NOTE_C4, NOTE_E4};  // C - E - G
int Csmajor[6] = {      0, NOTE_Cs3, NOTE_F3, NOTE_Gs3, NOTE_Cs4, NOTE_F4};  // C - E - G
int Dmajor[6] = {      0,       0, NOTE_D3, NOTE_A3, NOTE_D4, NOTE_Fs4}; // D - F# - A
int Dsmajor[6] = {      0,       0, NOTE_Ds3, NOTE_As3, NOTE_Ds4, NOTE_G4}; // D - F# - A
int Emajor[6] = {NOTE_E2, NOTE_B2, NOTE_E3, NOTE_Gs3,NOTE_B3, NOTE_E4};  // E - G# - B
int Fmajor[6] = {      0, NOTE_A2, NOTE_F3, NOTE_A3, NOTE_C4, NOTE_F4};  // F - A - C
int Fsmajor[6] = {      0, NOTE_As2, NOTE_Fs3, NOTE_As3, NOTE_Cs4, NOTE_Fs4};  // F - A - C
int Gmajor[6] = {NOTE_G2, NOTE_B2, NOTE_D3, NOTE_G3, NOTE_B3, NOTE_E4};  // G - B - D
int Gsmajor[6] = {NOTE_Gs2, NOTE_C3, NOTE_Ds3, NOTE_Gs3, NOTE_C4, NOTE_F4};  // G - B - D
int Amajor[6] = {      0, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_Cs4,NOTE_E4};  // A - C# - E
int Asmajor[6] = {      0, NOTE_As2, NOTE_F3, NOTE_As3, NOTE_D4,NOTE_F4};  // A - C# - E
int Bmajor[6] = {      0, NOTE_C4, NOTE_G3,NOTE_C3, NOTE_E4,NOTE_G4}; // B - D# - F#


const int Cminor[6] = {      0, NOTE_C3, NOTE_G3, NOTE_C4, NOTE_Ds4,NOTE_G4};  // C - D# - G
const int Dminor[6] = {      0,       0, NOTE_D3, NOTE_A3, NOTE_D4, NOTE_F4};  // D - F - A
const int Eminor[6] = {NOTE_E2, NOTE_B2, NOTE_E3, NOTE_G3, NOTE_B3, NOTE_E4};  // E - G - B
const int Fminor[6] = {NOTE_F2, NOTE_C3, NOTE_F3, NOTE_Gs3,NOTE_C4, NOTE_F4};  // F - G# - C
const int Gminor[6] = {NOTE_G2, NOTE_D3, NOTE_G3, NOTE_As3,NOTE_D3, NOTE_G4};  // G - A# - D
const int Aminor[6] = {      0, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_C4, NOTE_E4};  // A - C - E
const int Bminor[6] = {      0, NOTE_B2, NOTE_Fs3,NOTE_B3, NOTE_D4, NOTE_Fs4}; // B - D - F#

//                   E2, F2, F2#, G2, G2#, A2, A2#, B2
// C3, C3#, D3, D3#, E3, F3, F3#, G3, G3#, A3, A3#, B3
// C4, C4#, D4, D4#, E4, F4, F4#, G4, G4#, A4, A4#, B4
