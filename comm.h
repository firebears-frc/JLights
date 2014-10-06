//CRIO->Arduino First Bytes
		//Setting
	#define LT_SET_ALL 0x10 //set all lights
	#define LT_SET_ARM 0x1C //set arm lights
	#define LT_SET_LOG 0x1A //set logo lights
	#define LT_SET_UND 0x1B //set under lights
		
	#define LT_SET_COL 0x18 //sets color of default animation

    	//Notifications
    #define LT_HAS_S01 0x30 //Has Set strip 1
    #define LT_HAS_S02 0x31 //Has Set strip 2
    #define LT_HAS_S03 0x32 //Has Set strip 3
    #define LT_HAS_S12 0x33 //Has Set strip 1&2
    #define LT_HAS_S23 0x34 //Has Set strip 2&3
    #define LT_HAS_S13 0x35 //Has Set strip 1&3
    #define LT_HAS_ALL 0x36 //Has Set all strips

    #define LT_VERIFY 0x37 //Verification
	#define LT_NERROR 0x38 //error code

	#define LT_HAS_C01 0x39; //Has Set copper strip 1
	#define LT_HAS_C02 0x3A; //Has Set copper strip 2
	#define LT_HAS_C03 0x3B; //Has Set copper strip 3
	#define LT_HAS_C12 0x3C; //Has Set copper strip 1&2
	#define LT_HAS_C23 0x3D; //Has Set copper strip 2&3
	#define LT_HAS_C13 0x3E; //Has Set copper strip 1&3
	#define LT_HAS_DCS 0x3F; //Has Set Default Color or String

//second bytes: animations
	#define LT_ANIM_FB 0x21 //fire bears animation
	#define LT_ANIM_MV 0x22 //moving animation
	#define LT_ANIM_BL 0x23 //blink animation
	#define LT_ANIM_BN 0x24 //bouncing animation
	#define LT_ANIM_SW 0x25 //switching animations
	#define LT_ANIM_SP 0x26 //spinning animation
	#define LT_ANIM_PL 0x27 //pulse animation
	#define LT_ANIM_GR 0x28 //growing fire animation
	#define LT_ANIM_OC 0x29 //one color animation
	#define LT_ANIM_GL 0x2A //glowing animation

//second bytes: colors
	#define LT_COL_BRIGHT_RED 0x01
	#define LT_COL_MEDIUM_RED 0x02
	#define LT_COL_DULL_RED 0x03
	#define LT_COL_BRIGHT_YELLOW 0x04
	#define LT_COL_MEDIUM_YELLOW_A 0x05
	#define LT_COL_MEDIUM_YELLOW_B 0x06
	#define LT_COL_MEDIUM_ORANGE 0x07
	#define LT_COL_DULL_ORANGE 0x08
	#define LT_COL_BRIGHT_ORANGE 0x09
	#define LT_COL_ALIEN_BLUE 0x0A
	#define LT_COL_GREEN 0x0B

//second bytes: error codes
	#define LT_ERR_NSS 0x50 //couldn't set strip: No Such Strip
	#define LT_ERR_RWS 0x51	//Request Without Send
	#define LT_ERR_WSB 0x52	//Wrong Second Byte [verification]
	#define LT_ERR_NSA 0x53	//couldn't set strip: No Such Animation
	#define LT_ERR_NOC 0x54	//NOt Connected

//second bytes: Verification
    #define LT_MAGIC 0x4C //"I'm connected!" (magic byte)

//I2C info
	#define SLAVE_ADDRESS 0x04
