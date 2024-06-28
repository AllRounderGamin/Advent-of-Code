int prevMeasurement;
int answer = 0;

string? line;
StreamReader input = new ("input.txt");
line = input.ReadLine();
int newMeasurement = Int32.Parse(line);
line = input.ReadLine();

while(line != null){
    prevMeasurement = newMeasurement;
    newMeasurement = Int32.Parse(line);
    if (newMeasurement > prevMeasurement){
        answer++;
    }
    line = input.ReadLine();
}
input.Close();

Console.WriteLine(answer);

answer = 0;

int inputNum;
int windowOne, windowTwo, windowThree;
int lastOne, lastTwo, lastThree;
input = new ("input.txt");
line = input.ReadLine();
windowOne = Int32.Parse(line);
line = input.ReadLine();
newMeasurement = Int32.Parse(line);
windowOne += newMeasurement;
windowTwo = newMeasurement;
line = input.ReadLine();
newMeasurement = Int32.Parse(line);
windowOne += newMeasurement;
windowTwo += newMeasurement;
windowThree = newMeasurement;

lastOne = windowOne;
windowOne = 0;
inputNum = 3;
lastTwo = lastThree = 0;


while(line != null){
    switch (inputNum % 3){
        case 1:
            lastTwo = windowTwo;
            if (windowTwo > lastOne){
                answer++;
            }
            windowTwo = 0;
            break;
        case 2:
            lastThree = windowThree;
            if (windowThree > lastTwo){
                answer++;
            }
            windowThree = 0;
            break;
        case 0:
            lastOne = windowOne;
            if (windowOne > lastThree){
                answer++;
            }
            windowOne = 0;
            break;
    }
    newMeasurement = Int32.Parse(line);
    windowOne += newMeasurement;
    windowTwo += newMeasurement;
    windowThree += newMeasurement;
    inputNum++;
    line = input.ReadLine();
}
input.Close();

Console.WriteLine(answer);
