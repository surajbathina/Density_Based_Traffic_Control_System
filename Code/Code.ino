int IR_pin[12] = {22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33};
int led_Green[4] = {6, 7, 8, 9};
int led_Red[4] = {2, 3, 4, 5};
struct data
{
  int density;
  int lane;
} dt[4];

void setup()
{
  Serial.begin(9600);
  for (int i = 0; i < 12; i++)
  {
    pinMode(IR_pin[i], INPUT);
  }

  for (int i = 0; i < 4; i++)
  {
    pinMode(led_Green[i], OUTPUT);
    pinMode(led_Red[i], OUTPUT);
  }

  for (int i = 0; i < 4; i++)
  {
    digitalWrite(led_Green[i], LOW);
    digitalWrite(led_Red[i], LOW);
  }
}

void loop()
{
  acquire_data();
  sort();
  execute();
  for(int i=0;i<4;i++)
  {
  dt[i] .density=0;
  }
}

void acquire_data()
{
  int j = 0;

  for (int i = 0; i < 12; i++)
  {
    if ((i % 3) == 0 && i != 0)
    {
      j++;
    }

    if (digitalRead(IR_pin[i]) == HIGH)
    {
      (dt[j].density)++;
    }
    dt[j].lane = j;
  }
}

void sort()
{
  int swapd, swapl;
  for (int i = 0 ; i < 4; i++)
  {
    for (int j = 0; j < 4 - i - 1; j++)
    {
      if (dt[j].density < dt[j + 1].density)
      {
        swapd = dt[j].density;
        dt[j].density = dt[j + 1].density;
        dt[j + 1].density = swapd;
        swapl = dt[j].lane;
        dt[j].lane = dt[j + 1].lane;
        dt[j + 1].lane = swapl;
      }
    }
  }
}

void execute()
{
  digitalWrite(led_Green[dt[0].lane], HIGH);
  for (int k = 0; k < 4; k++)
  {
    if (k != dt[0].lane)
      digitalWrite(led_Red[k], HIGH);
  }
  delay(1000 * dt[0].density);

  for (int i = 0; i < 4; i++)
  {
    digitalWrite(led_Green[dt[0].lane], LOW);
    for (int k = 0; k < 4; k++)
    {
      if (k != dt[0].lane)
        digitalWrite(led_Red[k], LOW);
    }
  }
}
