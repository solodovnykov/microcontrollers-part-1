void timerActive(int isActive)
{
    if (isActive == 1) {

        doStructTime[4]();
        digitalWrite(dotPin, LOW);
        doNumber[10]();
        doStructTime[5]();
        digitalWrite(dotPin, 1);
        doNumber[10]();
        doStructTime[6]();
        doNumber[abs(7)]();
    }
    if (isActive == 0) {

        doStructTime[4]();
        digitalWrite(dotPin, LOW);
        doNumber[11]();
        doStructTime[5]();
        digitalWrite(dotPin, 1);
        doNumber[11]();
        doStructTime[6]();
        doNumber[abs(7)]();
    }
}

void hourVisual(int hour)
{
    if (hour >= 20 && hour < 25) {

        doStructTime[0]();
        digitalWrite(dotPin, LOW);
        doNumber[2]();
        doStructTime[1]();
        digitalWrite(dotPin, 1);
        doNumber[abs(20 - hour)]();
    }
    if (hour >= 10 && hour < 20) {
        doStructTime[0]();
        digitalWrite(dotPin, LOW);
        doNumber[1]();
        doStructTime[1]();
        digitalWrite(dotPin, 1);
        doNumber[abs(10 - hour)]();
    }
    if (hour < 10) {
        doStructTime[0]();
        digitalWrite(dotPin, LOW);
        doNumber[0]();
        doStructTime[1]();
        digitalWrite(dotPin, 1);
        doNumber[abs(hour)]();
    }
}

void minVisual(int minute)
{
    if (minute >= 50 && minute < 60) {

        doStructTime[2]();
        digitalWrite(dotPin, LOW);
        doNumber[5]();
        doStructTime[3]();
        digitalWrite(dotPin, 1);
        doNumber[abs(50 - minute)]();
    }
    if (minute >= 40 && minute < 50) {

        doStructTime[2]();
        digitalWrite(dotPin, LOW);
        doNumber[4]();
        doStructTime[3]();
        digitalWrite(dotPin, 1);
        doNumber[abs(40 - minute)]();
    }
    if (minute >= 30 && minute < 40) {

        doStructTime[2]();
        digitalWrite(dotPin, LOW);
        doNumber[3]();
        doStructTime[3]();
        digitalWrite(dotPin, 1);
        doNumber[abs(30 - minute)]();
    }

    if (minute >= 20 && minute < 30) {

        doStructTime[2]();
        digitalWrite(dotPin, LOW);
        doNumber[2]();
        doStructTime[3]();
        digitalWrite(dotPin, 1);
        doNumber[abs(20 - minute)]();
    }

    if (minute >= 10 && minute < 20) {

        doStructTime[2]();
        digitalWrite(dotPin, LOW);
        doNumber[1]();
        doStructTime[3]();
        digitalWrite(dotPin, 1);
        doNumber[abs(10 - minute)]();
    }
    if (minute < 10) {

        doStructTime[2]();
        digitalWrite(dotPin, LOW);
        doNumber[0]();
        doStructTime[3]();
        digitalWrite(dotPin, HIGH);
        doNumber[abs(minute)]();
    }
}

void secVisual(int sec)
{
    if (sec >= 50 && sec < 60) {

        doStructTime[4]();
        digitalWrite(dotPin, LOW);
        doNumber[5]();
        doStructTime[5]();
        digitalWrite(dotPin, 1);
        doNumber[abs(50 - sec)]();
        doStructTime[6]();
        doNumber[abs(7)]();
    }
    if (sec >= 40 && sec < 50) {

        doStructTime[4]();
        digitalWrite(dotPin, LOW);
        doNumber[4]();

        doStructTime[5]();
        digitalWrite(dotPin, 1);
        doNumber[abs(40 - sec)]();
        doStructTime[6]();
        doNumber[abs(7)]();
        //doStructTime[2]();
        //   doNumber[2]();
    }
    if (sec >= 30 && sec < 40) {

        doStructTime[4]();
        digitalWrite(dotPin, LOW);
        doNumber[3]();

        doStructTime[5]();
        digitalWrite(dotPin, HIGH);
        doNumber[abs(30 - sec)]();
        doStructTime[6]();
        doNumber[abs(7)]();
        //doStructTime[2]();
        //   doNumber[2]();
    }

    if (sec >= 20 && sec < 30) {

        doStructTime[4]();
        digitalWrite(dotPin, LOW);
        doNumber[2]();
        doStructTime[5]();
        digitalWrite(dotPin, 1);
        doNumber[abs(20 - sec)]();
        doStructTime[6]();
        doNumber[abs(7)]();
    }

    if (sec >= 10 && sec < 20) {

        doStructTime[4]();
        digitalWrite(dotPin, LOW);
        doNumber[1]();

        doStructTime[5]();
        digitalWrite(dotPin, 1);
        doNumber[abs(10 - sec)]();
        doStructTime[6]();
        doNumber[abs(7)]();
    }
    if (sec < 10) {

        doStructTime[4]();
        digitalWrite(dotPin, LOW);
        doNumber[0]();
        doStructTime[5]();
        digitalWrite(dotPin, 1);
        doNumber[abs(sec)]();
        doStructTime[6]();
    }
}
