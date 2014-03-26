

unsigned int fletcher16(char *data, unsigned int bytes )
{
  // slightly modified from http://en.wikipedia.org/wiki/Fletcher%27s_checksum

  unsigned int sum1 = 0xff, sum2 = 0xff, tlen;
  while (bytes)
  {
    tlen = bytes; // If byte size is variable, use this "tlen = bytes > 20 ? 20 : bytes;"
    bytes -= tlen;
    do
    {
      sum2 += sum1 += *data++;
    } while (--tlen);
    sum1 = (sum1 & 0xff) + (sum1 >> 8);
    sum2 = (sum2 & 0xff) + (sum2 >> 8);
  }
  /* Second reduction step to reduce sums to 8 bits */
  sum1 = (sum1 & 0xff) + (sum1 >> 8);
  sum2 = (sum2 & 0xff) + (sum2 >> 8);
  return sum2 << 8 | sum1;
}

int Background(void)
{
  int temp;
  // Add all the events to the event queue
  // Get inputs from COMM
  temp = GetComm();
  // Get inputs from Digital In
  // Get inputs from Timer?
  //
  return temp;
}

int GetComm(void)
{
  int checksum;
  if(Serial.available() > 11)
  {
    // Read the available data and check checksum
    if(Serial.peek() == ':')
    {
      MyData.header = Serial.read();
      MyData.command = Serial.read();
      Serial.readBytes(MyData.data, 8);
      Serial.readBytes(MyData.chksum, 2);
    //  MyData.data[4] = MyData.header; // Move the header into last position in data array to compute checksum
    //  checksum = MyData.chksum[0] + (MyData.chksum[1] << 8);
    //  if(checksum == fletcher16(MyData.data, 5))
    //  {
    //    // data is good
    //    return 1;
    //  }
    //  else
    //    return 0;
      Serial.write('=');
      return MyData.command;
    }
  } 
}

