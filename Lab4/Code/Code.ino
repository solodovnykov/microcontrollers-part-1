int pinA = 22;
int pinB = 23;
int pinC = 24;
int pinD = 25;
int pinE = 26;
int pinF = 27;
int pinG = 28;
int D1 = 21;
int D2 = 20;
int D3 = 19;
int D4 = 18;
int D5 = 17;
int D6 = 16;
int dotPin = 29;
int minute = 0;
int hour = 0;
int minuteTimer = 0;
int hourTimer = 0;
int isActive = 0;
int sec = 0;
void Number0(void);
void Number1(void);
void Number2(void);
void Number3(void);
void Number4(void);
void Number5(void);
void Number6(void);
void Number7(void);
void Number8(void);
void Number9(void);
void SumbolA(void);
void SumbolD(void);
void timeNumberCount1(void);
void timeNumberCount2(void);
void timeNumberCount3(void);
void timeNumberCount4(void);
void timeNumberCount5(void);
void timeNumberCount6(void);
void timeNumberCount0(void);
void hourVisual(void);
void minVisual(void);
void secVisual(void);
void timerActive(void);
void tickLogicShowTimer(void);
//void changeMinute(void);
void (*doStructTime[])(){ timeNumberCount1, timeNumberCount2, timeNumberCount3,
    timeNumberCount4, timeNumberCount5, timeNumberCount6, timeNumberCount0 };
void (*doNumber[])(){ Number0, Number1, Number2, Number3, Number4,
    Number5, Number6, Number7, Number8, Number9, SumbolA, SumbolD };
int pinInit[] = { pinA, pinB, pinC, pinD, pinE, pinF, pinG, D1, D2, D3, D4, D5, D6 };
void setup()
{
    pinMode(A3, INPUT_PULLUP);
    pinMode(A4, INPUT_PULLUP);
    pinMode(A5, INPUT_PULLUP);
    pinMode(A6, INPUT_PULLUP);
    pinMode(37, OUTPUT);
    for (int i = 0; i < 14; i++) {
        pinMode(pinInit[i], OUTPUT);
    }

    cli();

    

 
   
ASSR = (1 << AS2);
  TCCR2B = (1 << CS22);
  while (ASSR & ((1 << TCN2UB) | (1 << OCR2BUB) | (1 << TCR2BUB)))
  {
  }
  TIFR2 = 0x00;
  TIMSK2 = (1 << TOIE2);
    sei();
}
int ButtonHourValue = 0;
int ButtonMinuteValue = 0;
int onBtnHour = 0;
int onBtnMinute = 0;
int ButtonTimerSetupValue = 0;
int onBtnTimerSetup = 0;
int ButtonActivateValue = 0;
int onBtnActivate = 0;
void loop()
{
    if (isActive == 1) {

        if (hour == hourTimer && minute == minuteTimer) {
            digitalWrite(37, HIGH);
        }
    }
    if (hour != hourTimer || minute != minuteTimer) {
        digitalWrite(37, LOW);
    }

    {

        ButtonTimerSetupValue = !digitalRead(A5);
        if (ButtonTimerSetupValue != 0) {
            onBtnTimerSetup = !onBtnTimerSetup;
        }
        while (ButtonTimerSetupValue == 0 && onBtnTimerSetup == 1) {
            tickLogicShowTimer(hourTimer, minuteTimer, isActive);
            {
                ButtonHourValue = !digitalRead(A3);
                if (ButtonHourValue != 0) {
                    onBtnHour = !onBtnHour;
                }

                if (ButtonHourValue == 0 && onBtnHour == 1) {

                    hourTimer += 1;
                    onBtnHour = 0;
                }
            }

            {
                ButtonActivateValue = !digitalRead(A6);
                if (ButtonActivateValue != 0) {
                    onBtnActivate = !onBtnActivate;
                }

                if (ButtonActivateValue == 0 && onBtnActivate == 1) {

                    isActive = !isActive;
                    onBtnActivate = 0;
                }
            }

            {
                ButtonMinuteValue = !digitalRead(A4);

                if (ButtonMinuteValue != 0) {
                    onBtnMinute = !onBtnMinute;
                }

                if (ButtonMinuteValue == 0 && onBtnMinute == 1) {

                    minuteTimer += 1;
                    onBtnMinute = 0;
                }
            }
            ButtonTimerSetupValue = !digitalRead(A5);

            if (ButtonTimerSetupValue != 0) {
                onBtnTimerSetup = !onBtnTimerSetup;
            }
        }

        //   digitalRead(A2);
        //    digitalRead(A3);
    }
    {
        ButtonHourValue = !digitalRead(A3);
        if (ButtonHourValue != 0) {
            onBtnHour = !onBtnHour;
        }

        if (ButtonHourValue == 0 && onBtnHour == 1) {

            hour += 1;
            onBtnHour = 0;
        }
    }
    {
        ButtonMinuteValue = !digitalRead(A4);

        if (ButtonMinuteValue != 0) {
            onBtnMinute = !onBtnMinute;
        }

        if (ButtonMinuteValue == 0 && onBtnMinute == 1) {

            minute += 1;
            onBtnMinute = 0;
        }
    }

    tickLogicShow(hour, minute, sec);
}

void tickLogicShow(int hour, int minute, int sec)
{

    hourVisual(hour);
    minVisual(minute);

    secVisual(sec);
}

void tickLogicShowTimer(int hour, int minute, int isActive)
{

    hourVisual(hour);
    minVisual(minute);
    timerActive(isActive);
}

ISR(TIMER2_OVF_vect)
{

    if (sec == 60) {
        sec = 0;
        minute += 1;
    }
    if (minute == 60 && sec == 0) {
        hour += 1;
        minute = 0;
    }
    if (hour == 24 && minute == 0 && sec == 0) {
        hour = 0;
        minute = 0;
        sec = 0;
    }
    if (hour >= 24) {
        hour = 0;
    }
    if (minute >= 60) {
        minute = 0;
    }
    sec += 1;
}
