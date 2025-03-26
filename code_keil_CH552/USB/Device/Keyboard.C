#include "./Public/CH552.H"                                                     
#include "./Public/DEBUG.H" 
#include <string.h>
#include <stdio.h>

#define THIS_ENDP0_SIZE         DEFAULT_ENDP0_SIZE
#define CapsLockLED 0x02
UINT8 Ep0Buffer[8 > (THIS_ENDP0_SIZE + 2) ? 8 : (THIS_ENDP0_SIZE + 2)];         // Endpoint 0 buffer
UINT8 Ep1Buffer[64 > (MAX_PACKET_SIZE + 2) ? 64 : (MAX_PACKET_SIZE + 2)];       // Endpoint 1 buffer
UINT8   SetupReq,SetupLen,Ready,Count,FLAG,UsbConfig,LED_VALID;
PUINT8  pDescr;                                                                 //USB descriptor
USB_SETUP_REQ   SetupReqBuf;
#define UsbSetupBuf     ((PUSB_SETUP_REQ)Ep0Buffer)

#define BUFMAX 8

UINT8 HIDKey[BUFMAX] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}; // HID key buffer

void USBDeviceInit();
void Enp1IntIn();

// HID Keycodes
#define KEY_CTRL  0x01
#define KEY_ALT   0x04
#define KEY_DEL   0x4C
#define KEY_TAB   0x2B
#define KEY_A     0x04
#define KEY_DELETE 0x4C

// Function to send a key combination
void SendKeyCombo(UINT8 modifier, UINT8 key) {
    HIDKey[0] = modifier; // Modifier keys (e.g., Ctrl, Alt)
    HIDKey[2] = key;      // Main key
    Enp1IntIn();          // Send the key press
    HIDKey[0] = 0x00;     // Release modifier
    HIDKey[2] = 0x00;     // Release key
    Enp1IntIn();          // Send the key release
}

// Function to send a string
void SendString(const char *str) {
    while (*str) {
        HIDKey[2] = *str - 93; // Map ASCII to HID keycode (simplified for example)
        Enp1IntIn();           // Send key press
        HIDKey[2] = 0x00;      // Release key
        Enp1IntIn();           // Send key release
        str++;
    }
}

sbit  LED1 = P3^2;

// Main function
void main() {
    CfgFsys();       // Configure system clock
    mDelaymS(5);     // Small delay
    USBDeviceInit(); // Initialize USB device

    while (1) {
        // Make the LED on P3^2 blink
        LED1 = 1;
        mDelaymS(500);

        // Step 1: Press Ctrl + Alt + Del
        SendKeyCombo(KEY_CTRL | KEY_ALT, KEY_DEL);

        // Make the LED on P3^2 blink twice
        LED1 = 0;
        mDelaymS(200);
        LED1 = 1;
        mDelaymS(200);
        LED1 = 0;
        mDelaymS(200);
        LED1 = 1;
        mDelaymS(500);

        // Step 2: Type email "example@mail.com"
        SendString("example@mail.com");

        // Make the LED on P3^2 three times
        LED1 = 0;
        mDelaymS(200);
        LED1 = 1;
        mDelaymS(200);
        LED1 = 0;
        mDelaymS(200);
        LED1 = 1;
        mDelaymS(200);
        LED1 = 0;
        mDelaymS(200);
        LED1 = 1;
        mDelaymS(500);

        // Step 3: Press Tab
        SendKeyCombo(0x00, KEY_TAB);

        // Step 4: Type password "Secret"
        SendString("Secret");

        // Make the LED on P3^2 four times
        LED1 = 0;
        mDelaymS(200);
        LED1 = 1;
        mDelaymS(200);
        LED1 = 0;
        mDelaymS(200);
        LED1 = 1;
        mDelaymS(200);
        LED1 = 0;
        mDelaymS(200);
        LED1 = 1;
        mDelaymS(200);
        LED1 = 0;
        mDelaymS(200);
        LED1 = 1;
        mDelaymS(500);

        // Step 5: Wait 500ms
        mDelaymS(500);

        // Step 6: Press Ctrl + A
        SendKeyCombo(KEY_CTRL, KEY_A);

        // Step 7: Press Delete
        SendKeyCombo(0x00, KEY_DELETE);

        LED1 = 0;
        mDelaymS(500);
        LED1 = 1;
        mDelaymS(500);
        LED1 = 0;

        while (1); // Stop execution after completing the sequence
    }
}

// USB Device Initialization
void USBDeviceInit() {
    // USB initialization code here
    IE_USB = 0;
    USB_CTRL = 0x00;                                                           // USB device mode
    UEP0_DMA = Ep0Buffer;                                                      // 0
    UEP1_DMA = Ep1Buffer;                                                      // 1
    UEP4_1_MOD = ~(bUEP4_RX_EN | bUEP4_TX_EN |bUEP1_RX_EN | bUEP1_BUF_MOD) | bUEP4_TX_EN;   // 64-byte IN, 0 OUT
    UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;                                 //OUT ACK IN NAK
    UEP1_CTRL = bUEP_T_TOG | UEP_T_RES_NAK;
        
    USB_DEV_AD = 0x00;
    UDEV_CTRL = bUD_PD_DIS;                                                    // DP/DM pull-up disable
    USB_CTRL = bUC_DEV_PU_EN | bUC_INT_BUSY | bUC_DMA_EN;                      // USB DMA interrupt enable and automatic NAK
    UDEV_CTRL |= bUD_PORT_EN;                                                  // USB port enable
    USB_INT_FG = 0xFF;                                                         // Clear interrupt flags
    USB_INT_EN = bUIE_SUSPEND | bUIE_TRANSFER | bUIE_BUS_RST;
    IE_USB = 1;
}

// USB Endpoint 1 Interrupt IN (Send HID data)
void Enp1IntIn() {
    // Send HIDKey buffer to the host
    memcpy( Ep1Buffer, HIDKey, sizeof(HIDKey));                              //�����ϴ�����
    UEP1_T_LEN = sizeof(HIDKey);                                             //�ϴ����ݳ���
    UEP1_CTRL = UEP1_CTRL & ~ MASK_UEP_T_RES | UEP_T_RES_ACK;                //������ʱ�ϴ����ݲ�Ӧ��ACK
}