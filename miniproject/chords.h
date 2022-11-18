
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

/// Major
int Cmaj[3]   =  {NOTE_C3, NOTE_E3, NOTE_G3};       //  C - E - G
int Csmaj[3]  =  {NOTE_Cs3, NOTE_F3, NOTE_Gs3};     //  C# - F - G#
int Dmaj[3]   =  {NOTE_D3, NOTE_Fs3, NOTE_A3};      //  D - F# - A
int Dsmaj[3]  =  {NOTE_Ds3, NOTE_G3, NOTE_As3};     //  D# - G - A#
int Emaj[3]   =  {NOTE_E3, NOTE_Gs3, NOTE_B3};      //  E - G# - B
int Fmaj[3]   =  {NOTE_F3, NOTE_A3, NOTE_C4};       //  F - A - C
int Fsmaj[3]  =  {NOTE_Fs3, NOTE_As3, NOTE_Cs4};    //  F# - A# - C
int Gmaj[3]   =  {NOTE_G3, NOTE_B3, NOTE_D4};       //  G - B - D
int Gsmaj[3]  =  {NOTE_Gs2, NOTE_C4, NOTE_Ds4};     //  G# - C - D#
int Amaj[3]   =  {NOTE_A3, NOTE_Cs4, NOTE_E4};      //  A - C# - E
int Asmaj[3]  =  {NOTE_As3, NOTE_D4, NOTE_F4};      //  A# - D - F
int Bmaj[3]   =  {NOTE_B3, NOTE_G3, NOTE_C3};       //  B - D# - F#

/// Minor
int Cmin[3]   =  {NOTE_C3, NOTE_Ds3, NOTE_G3};      //  C - D# - G
int Csmin[3]  =  {NOTE_Cs3, NOTE_E3, NOTE_Gs3};     //  C# - E - G#
int Dmin[3]   =  {NOTE_D3, NOTE_F3, NOTE_A3};       //  D - F - A
int Dsmin[3]  =  {NOTE_Ds3, NOTE_Fs3, NOTE_As3};    //  D# - F# - A#
int Emin[3]   =  {NOTE_E3, NOTE_G3, NOTE_B3};       //  E - G - B
int Fmin[3]   =  {NOTE_F3, NOTE_Gs3, NOTE_C4};      //  F - G# - C
int Fsmin[3]  =  {NOTE_Fs3, NOTE_A3, NOTE_Cs4};     //  F# - A - C
int Gmin[3]   =  {NOTE_G3, NOTE_As3, NOTE_D4};      //  G - A# - D
int Gsmin[3]  =  {NOTE_Gs3, NOTE_B3, NOTE_Ds4};     //  G# - B - D#
int Amin[3]   =  {NOTE_A3, NOTE_C4, NOTE_E4};       //  A - C - E
int Asmin[3]  =  {NOTE_As3, NOTE_Cs4, NOTE_F4};     //  A# - C# - F
int Bmin[3]   =  {NOTE_B3, NOTE_D4, NOTE_Fs4};      //  B - D - F#

/// Diminished
int Cdim[3]   =  {NOTE_C3, NOTE_Ds3, NOTE_Fs3};     //  C - D# - F#
int Csdim[3]  =  {NOTE_Cs3, NOTE_E3, NOTE_G3};      //  C# - E - G
int Ddim[3]   =  {NOTE_D3, NOTE_F3, NOTE_Gs3};      //  D - F - G#
int Dsdim[3]  =  {NOTE_Ds3, NOTE_Fs3, NOTE_A3};     //  D# - F# - A
int Edim[3]   =  {NOTE_E3, NOTE_G3, NOTE_As3};      //  E - G - A#
int Fdim[3]   =  {NOTE_F3, NOTE_Gs3, NOTE_B3};      //  F - G# - B
int Fsdim[3]  =  {NOTE_Fs3, NOTE_A3, NOTE_C4};      //  F# - A - C
int Gdim[3]   =  {NOTE_G3, NOTE_As3, NOTE_Cs4};     //  G - A# - C#
int Gsdim[3]  =  {NOTE_Gs3, NOTE_B3, NOTE_D4};      //  G# - B - D
int Adim[3]   =  {NOTE_A3, NOTE_C4, NOTE_Ds4};      //  A - C - D#
int Asdim[3]  =  {NOTE_As3, NOTE_Cs4, NOTE_E4};     //  A# - C# - E
int Bdim[3]   =  {NOTE_B3, NOTE_D4, NOTE_F4};       //  B - D - F
