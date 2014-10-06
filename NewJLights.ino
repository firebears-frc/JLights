#include <LPD8806.h>
#include <SPI.h>
#include <Adafruit_NeoPixel.h>
#include "Animation.h"
#include "MovingAnimation.h"
#include "SpinningAnimation.h"
#include "PulseAnimation.h"
#include "BouncingAnimation.h"
#include "FireBearsAnimation.h"
#include "BlinkAnimation.h"
#include "CatchFire.h"
#include "OneColor.h"
#include "Words.h"
#include "Glowing.h"
#include <Wire.h>
#include "strips.h"
#include "comm.h"

Adafruit_NeoPixel strips[3] = {
  Adafruit_NeoPixel(NUM_PIXL_0, PIN_STRIP_0, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXL_1, PIN_STRIP_1, NEO_GRB + NEO_KHZ800),
  Adafruit_NeoPixel(NUM_PIXL_2, PIN_STRIP_2, NEO_GRB + NEO_KHZ800)
};

LPD8806 dc_strips[3] = {
  LPD8806(NUM_PICL_0, DAT_STRIP_0, CLK_STRIP_0),
  LPD8806(NUM_PICL_1, DAT_STRIP_1, CLK_STRIP_1),
  LPD8806(NUM_PICL_2, DAT_STRIP_2, CLK_STRIP_2)
};

variables_t *G_Vars;

FireBearsAnimation *fb;
MovingAnimation *mv;
BlinkAnimation *bl;
BouncingAnimation *bn;
CatchFire *cf;
OneColor *oc;
Words *wd;
Glowing *gl;

char ByteA = LT_NERROR; //error
char ByteB = LT_ERR_RWS; //request without send
char RecvA[16];
char RecvB[16];

char AtRcv = 0;
boolean NullPacket = false;

//Temporary Variable Values For Recieving Stuff
boolean FirstByte = true;
char fc[2];

uint8_t DoDecode = 0;
uint8_t GDefCol = 1;
uint8_t GDefStr = 0;

void reset_gvars(int strip, uint8_t animType) {
  G_Vars[strip].anim_type = animType;
  G_Vars[strip].progress = 0;
  G_Vars[strip].time = 0;
  G_Vars[strip].isSparking = true;
  G_Vars[strip].isPausing = true;
  G_Vars[strip].toQuit = false;
  G_Vars[strip].lastTime = 0;
  G_Vars[strip].SLastTime = 0;
  G_Vars[strip].reset = true;
  G_Vars[strip].mode = 0;
  G_Vars[strip].defColInPallet = 9;
  G_Vars[strip].Goto_Anim = ALLL_ANIM;
}

void strip_init(boolean isSPI, int strip, uint8_t len, uint8_t animType) {
  // Initialize and reset the LED strip
  if(isSPI) {
    dc_strips[strip-3].begin();
    for (int p=0; p<G_Vars[strip-3].color_len; p++) {
      dc_strips[strip-3].setPixelColor(p, 0);
      dc_strips[strip-3].show();
    }
  }else{
    strips[strip].begin();
    for (int p=0; p<G_Vars[strip].color_len; p++) {
      strips[strip].setPixelColor(p, 0);
      strips[strip].show();
    }
  }
  
  //global vars...
  Serial.println("strip initing");
  int objectCount = (len/5)+1;
  G_Vars[strip].color = new uint32_t[len];
  G_Vars[strip].color_store = new uint32_t[len];
  G_Vars[strip].color_pos = new uint8_t[objectCount];
  G_Vars[strip].color_hom = new uint8_t[objectCount];
  G_Vars[strip].color_dir = new uint8_t[objectCount*5];
  G_Vars[strip].objectCount = objectCount;  reset_gvars(strip, animType);
  G_Vars[strip].color_len = len;
  G_Vars[strip].isCopper = isSPI;
  Serial.println("strip inited");
  return;
}

static inline void na_reset(void) {
  int i, p;
  Serial.println("reset");
  delay(100);
  
//  delay(100);
  cf = new CatchFire();
  fb = new FireBearsAnimation();
  mv = new MovingAnimation();
  bl = new BlinkAnimation();
  bn = new BouncingAnimation();
  oc = new OneColor();
//  wd = new Words();
  gl = new Glowing();
  Serial.print("classes made, ");
  print_free_bytes();
  delay(100);
  Serial.println("set strips.."); delay(100);
  strip_init(false,0, NUM_PIXL_0, ALLL_ANIM);
  strip_init(false,1, NUM_PIXL_1, ALLL_ANIM);
  strip_init(false,2, NUM_PIXL_2, ALLL_ANIM);

  strip_init(true,3, NUM_PICL_0, CAFR_ANIM);
  strip_init(true,4, NUM_PICL_1, CAFR_ANIM);
  strip_init(true,5, NUM_PICL_2, CAFR_ANIM);
}

void setup() {
  G_Vars = new variables_t[/*STRIP_COUNT+SPIIP_COUNT*/6];
  Serial.begin(9600);
  Serial.print("JLights: loading.... / ");
  print_free_bytes();
  delay(100);
  Wire.begin(SLAVE_ADDRESS);       // join i2c bus with address SLAVE_ADRESS (
  Wire.onReceive(na_receiveEvent); // register event
  Wire.onRequest(na_requestEvent); // register event
  na_reset();
  Serial.print("ANIMATION(done loading!), ");
  print_free_bytes();
  delay(100);
  #ifdef BACKUP
  pinMode(12, INPUT);
  #endif
}

void na_animate(int strip) {
  if((G_Vars[strip].anim_type==ALLL_ANIM) && (G_Vars[strip].SLastTime+5000 <= millis())) {
    G_Vars[strip].SLastTime += 5000;
    G_Vars[strip].mode++;
    if(G_Vars[strip].mode >4) {
      G_Vars[strip].mode= 0;
    }
    G_Vars[strip].reset = true;
  }
  if(G_Vars[strip].anim_type == FIRE_ANIM || ((G_Vars[strip].mode == 0)&&G_Vars[strip].anim_type==ALLL_ANIM)) {
    if(G_Vars[strip].reset) {
      fb->reset(&G_Vars[strip]);
    }
    fb->loop(&G_Vars[strip]);
  }else if(G_Vars[strip].anim_type == MOVE_ANIM || ((G_Vars[strip].mode == 1)&&G_Vars[strip].anim_type==ALLL_ANIM)) {
    if(G_Vars[strip].reset) {
      mv->reset(&G_Vars[strip]);
    }
    mv->loop(&G_Vars[strip]);
  }else if(G_Vars[strip].anim_type == BLNK_ANIM || ((G_Vars[strip].mode == 2)&&G_Vars[strip].anim_type==ALLL_ANIM)) {
    if(G_Vars[strip].reset) {
      bl->reset(&G_Vars[strip]);
    }
    bl->loop(&G_Vars[strip]);
  }else if(G_Vars[strip].anim_type == BNCE_ANIM || ((G_Vars[strip].mode == 3)&&G_Vars[strip].anim_type==ALLL_ANIM)) {
    if(G_Vars[strip].reset) {
      bn->reset(&G_Vars[strip]);
    }
    bn->loop(&G_Vars[strip]);
  }else if(G_Vars[strip].anim_type == CAFR_ANIM) {
    if(G_Vars[strip].reset) {
      cf->reset(&G_Vars[strip]);
    }
    cf->loop(&G_Vars[strip]);
    if(G_Vars[strip].toQuit) {
      G_Vars[strip].anim_type = G_Vars[strip].Goto_Anim;
      G_Vars[strip].Goto_Anim = FIRE_ANIM;
      G_Vars[strip].lastTime = millis();
      G_Vars[strip].SLastTime = millis();
      G_Vars[strip].mode = 0;
    }
  }else if(G_Vars[strip].anim_type == ONCO_ANIM) {
    if(G_Vars[strip].reset) {
      oc->reset(&G_Vars[strip], GDefCol);
    }
    oc->loop(&G_Vars[strip]);
  }else if(G_Vars[strip].anim_type == WORD_ANIM) {
    if(G_Vars[strip].reset) {
      wd->reset(&G_Vars[strip]);
    }
    wd->loop(&G_Vars[strip]);
    if(G_Vars[strip].toQuit) {
      G_Vars[strip].anim_type = ONCO_ANIM;
    }
  }else if((G_Vars[strip].anim_type == GLOW_ANIM) || ((G_Vars[strip].mode == 4)&&G_Vars[strip].anim_type==ALLL_ANIM)) {
    if(G_Vars[strip].reset) {
      gl->reset(&G_Vars[strip]);
    }
    gl->loop(&G_Vars[strip]);
  }
  int i;
  if(strip >= 3) {
    for (i = 0; i < G_Vars[strip].color_len; i++) {//draw
      dc_strips[strip-3].setPixelColor(i, G_Vars[strip].color[i]);
    }
    dc_strips[strip-3].show();
  }else{
    for (i = 0; i < G_Vars[strip].color_len; i++) {//draw
      strips[strip].setPixelColor(i, G_Vars[strip].color[i]);
    }
    strips[strip].show();
  }
  G_Vars[strip].reset = false;
}

void loop() {
//  Serial.println("loop");  delay(100);
  while(DoDecode) {
    na_decodeRecieve(RecvA[DoDecode],RecvB[DoDecode]);
    DoDecode--;
  }
  for(int ii = 0; ii < STRIP_COUNT+SPIIP_COUNT; ii++) {
    na_animate(ii);
  }
  #ifdef BACKUP
  if(digitalRead(12)) {
    na_setStrip(0, ONCO_ANIM);
    na_setStrip(1, ONCO_ANIM);
    na_setStrip(2, ONCO_ANIM);
    na_setStrip(3, ONCO_ANIM);
    na_setStrip(4, ONCO_ANIM);
    na_setStrip(5, ONCO_ANIM);
  }else{
    na_setStrip(0, ALLL_ANIM);
    na_setStrip(1, ALLL_ANIM);
    na_setStrip(2, ALLL_ANIM);
    na_setStrip(3, ALLL_ANIM);
    na_setStrip(4, ALLL_ANIM);
    na_setStrip(5, ALLL_ANIM);
  }
  #endif
}

void na_setStrip(int stripToSet, char setTo) {
  G_Vars[stripToSet].reset = true;
  if(setTo == 0x21) {
    reset_gvars(stripToSet, FIRE_ANIM);
  } else if(setTo == 0x22) {
    reset_gvars(stripToSet, MOVE_ANIM);
  } else if(setTo == 0x23) {
    reset_gvars(stripToSet, BLNK_ANIM);
  } else if(setTo == 0x24) {
    reset_gvars(stripToSet, BNCE_ANIM);
  } else if(setTo == 0x25) {
    reset_gvars(stripToSet, ALLL_ANIM);
  } else if(setTo == 0x26) {
    reset_gvars(stripToSet, SPIN_ANIM);
  } else if(setTo == 0x27) {
    reset_gvars(stripToSet, PULS_ANIM);
  } else if(setTo == 0x28) {
    reset_gvars(stripToSet, CAFR_ANIM);
  } else if(setTo == 0x29) {
    reset_gvars(stripToSet, ONCO_ANIM);
  } else if(setTo == 0x2A) {
    reset_gvars(stripToSet, GLOW_ANIM);
  } else {
    ByteA = LT_NERROR; //error
    ByteB = LT_ERR_NSA; //no such animation
  }
}

static void na_set_s00(char p_B2) {
    na_setStrip(0, p_B2);
}

static void na_set_s11(char p_B2) {
    na_setStrip(1, p_B2);
}

static void na_set_s22(char p_B2) {
    na_setStrip(2, p_B2);
}

static void na_set_s33(char p_B2) {
    na_setStrip(3, p_B2);
}

static void na_set_s44(char p_B2) {
    na_setStrip(4, p_B2);
}

static void na_set_s55(char p_B2) {
    na_setStrip(5, p_B2);
}

static void na_set_s01(char p_B2) {
	na_set_s00(p_B2);
    na_set_s11(p_B2);
}

static inline void na_set_all(char p_B2) {
	na_set_s01(p_B2); //0, 1
    na_set_s22(p_B2);
    na_set_s33(p_B2);
    na_set_s44(p_B2);
    na_set_s55(p_B2);
}

const char *setCodes[8] = {
	"all strips",
	"strip 1",
	"strip 2",
	"strip 3",
	"strip 1 & 2",
	"strip 2 & 3",
	"strip 1 & 3",
	"verify"
};

void na_decodeRecieve(char p_B1, char p_B2) {
  uint8_t f_B = p_B2 - 0x10;

  ByteB = p_B2; //to: value of p_B2
  Serial.print((int)ByteB);
  Serial.print(",");
  Serial.print((int)0x53);
  if(f_B < 8)
    Serial.println(setCodes[f_B]);
  if(p_B1 == 0x10) {
    na_set_all(p_B2);
    ByteA = LT_HAS_ALL; //set all strips
  }else if(p_B1 == 0x11) {
    na_set_s00(p_B2);
    ByteA = LT_HAS_S01; //set strip 1
  }else if(p_B1 == 0x12) {
    na_set_s11(p_B2);
    ByteA = LT_HAS_S02; //set strip 2
  }else if(p_B1 == 0x13) {
    na_set_s22(p_B2);
    ByteA = LT_HAS_S03; //set strip 3
  }else if(p_B1 == 0x14) {
	na_set_s01(p_B2); //0, 1
    ByteA = LT_HAS_S12; //set strip 1&2
  }else if(p_B1 == 0x15) {
    na_setStrip(1, p_B2);
    na_setStrip(2, p_B2);
    ByteA = LT_HAS_S23; //set strip 2&3
  }else if(p_B1 == 0x16) {
    na_setStrip(0, p_B2);
    na_setStrip(2, p_B2);
    ByteA = LT_HAS_S13; //set strip 1&3
  }else if(p_B1 == 0x17) { //test connection
    if(p_B2 == 0x4C) {
      ByteA = LT_VERIFY; //verification
      ByteB = LT_MAGIC; //magic byte
    }else{
      ByteA = LT_NERROR; //error
      ByteB = LT_ERR_WSB; //wrong second byte[verify]
    }
  }else if(p_B1 == 0x18) { //Set Default Color
    GDefCol = p_B2;
    ByteA = LT_HAS_DCS;
  }else if(p_B1 == 0x19) { //Set Default String
    GDefStr = p_B2;
    ByteA = LT_HAS_DCS;
  }else if(p_B1 == 0x1A) { //Set Copper Strip 1
    na_setStrip(3, p_B2);
    ByteA = LT_HAS_C01;
  }else if(p_B1 == 0x1B) { //Set Copper Strip 2
    na_setStrip(4, p_B2);
    ByteA = LT_HAS_C02;
  }else if(p_B1 == 0x1C) { //Set Copper Strip 3
    na_setStrip(5, p_B2);
    ByteA = LT_HAS_C03;
  }else if(p_B1 == 0x1D) { //Set Copper Strip 1&2
    na_setStrip(3, p_B2);
    na_setStrip(4, p_B2);
    ByteA = LT_HAS_C12;
  }else if(p_B1 == 0x1E) { //Set Copper Strip 2&3
    na_setStrip(4, p_B2);
    na_setStrip(5, p_B2);
    ByteA = LT_HAS_C23;
  }else if(p_B1 == 0x1F) { //Set Copper Strip 1&3
    na_setStrip(5, p_B2);
    na_setStrip(3, p_B2);
    ByteA = LT_HAS_C13;
  }else{
    Serial.println("ERROR");
    ByteA = LT_NERROR; //error
    ByteB = LT_ERR_NSS; //couldn't send strip: no such strip
  }
}

static inline void na_process_byte(byte p_byte) {
  if(FirstByte) {
    fc[0] = p_byte; // receive byte as a character
    FirstByte = false;
  }else{
    fc[1] = p_byte; // receive byte as a character
    RecvA[DoDecode] = fc[0];
    RecvB[DoDecode] = fc[1];
    DoDecode++;
    FirstByte = true;
  }
}

void na_receiveEvent(int howMany)
{
//  Serial.println("R");
  //Check If Packet Is Null
  if(howMany == 0) {
    Serial.println("No byte packet!");
    NullPacket = true;
    return;
  }else{
    NullPacket = false;
  }

  //Check Byte Count
  if(howMany != 2) {
    Serial.println();
    Serial.print("wrong packet size: not 2: ");
    Serial.println(howMany);
    return;
  }

  //loop through all bytes
  while(Wire.available() > 0)
  {
    na_process_byte(Wire.read()); // receive byte as a character
  }

  //Debugging Information
  Serial.print("RECV EVENT(");
  Serial.print(howMany);
  Serial.print("):");
  Serial.print((int)RecvA);
  Serial.print(",");
  Serial.println((int)RecvB);
}

void na_requestEvent()
{
  char Sender[2];
  if(NullPacket) {
    return;
  }
  Serial.print("Sending:");
  // respond with message of 2 bytes
  Serial.print((int)ByteA);
  Serial.print(",");
  Serial.print((int)ByteB);
  Serial.print("...");
  Sender[0] = ByteA;
  Sender[1] = ByteB;
  Wire.write(Sender);
  Serial.println("sent!");
  ByteA = LT_NERROR; //error
  ByteB = LT_ERR_RWS; //request without send
}

void print_free_bytes(void) {
	Serial.print("free:");
	Serial.println(memoryFree());
}

extern int __bss_end;
extern void *__brkval;

static inline int memoryFree() {
  int freeValue;
  if((int)__brkval == 0)
    freeValue = ((int)&freeValue) - ((int)&__bss_end);
  else
    freeValue = ((int)&freeValue) - ((int)__brkval);
  return freeValue;
}
