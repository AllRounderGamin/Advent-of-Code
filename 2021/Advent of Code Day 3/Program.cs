string? line;
StreamReader input = new ("input.txt");
line = input.ReadLine();

int[] oneBits = new int[line.Length];
int numbersRecorded = 0;
for (int i = 0; i < oneBits.Length; i++){
    oneBits[i] = 0;
}

while (line != null){
    for (int i = 0; i < line.Length; i++){
        if (line[i] == '1'){
            oneBits[i] += 1;
        }
    }
    numbersRecorded++;
    line = input.ReadLine();
}
input.Close();

int gamma = 0;
int epsilon = 0;

for (int i = 0; i < oneBits.Length; i++){
    if (oneBits[i] > numbersRecorded - oneBits[i]){
        gamma += (int)Math.Pow(2, oneBits.Length - i - 1);
    } else {
        epsilon += (int)Math.Pow(2, oneBits.Length - i - 1);
    }
}

Console.WriteLine(gamma * epsilon);


input = new ("input.txt");
line = input.ReadLine();
List<string> startsWithOne, startsWithZero, oxygenList, carbonList;
startsWithOne = [];
startsWithZero = [];


while (line != null){
    if (line[0] == '1'){
        startsWithOne.Add(line);
    } else {
        startsWithZero.Add(line);
    }
    line = input.ReadLine();
}
input.Close();


int oxygen = 0;
int carbonDio = 0;
int currentIndex = 1;


if (oneBits[0] >= numbersRecorded - oneBits[0]){
    oxygenList = new (startsWithOne);
    carbonList = new (startsWithZero);
} else {
    oxygenList = new (startsWithZero);
    carbonList = new (startsWithOne);
}
startsWithOne.Clear();
startsWithZero.Clear();

while (oxygenList.Count > 1 & oxygenList[0].Length > currentIndex){
    foreach (string num in oxygenList){
        if (num[currentIndex] ==  '1'){
            startsWithOne.Add(num);
        } else {
            startsWithZero.Add(num);
        }
    }
    if (startsWithOne.Count >= startsWithZero.Count){
        oxygenList = new(startsWithOne);
    } else {
        oxygenList = new(startsWithZero);
    }
    currentIndex++;
    startsWithOne.Clear();
    startsWithZero.Clear();
}

currentIndex = 1;

while (carbonList.Count > 1 & carbonList[0].Length > currentIndex){
    foreach (string num in carbonList){
        if (num[currentIndex] ==  '1'){
            startsWithOne.Add(num);
        } else {
            startsWithZero.Add(num);
        }
    }
    if (startsWithZero.Count <= startsWithOne.Count){
        carbonList = new(startsWithZero);
    } else {
        carbonList = new(startsWithOne);
    }
    currentIndex++;
    startsWithOne.Clear();
    startsWithZero.Clear();
}

for (int i = 0; i < oxygenList[0].Length; i++){
    if (oxygenList[0][i] == '1'){
        oxygen += (int)Math.Pow(2, oxygenList[0].Length - i - 1);
    }
    if (carbonList[0][i] == '1'){
        carbonDio += (int)Math.Pow(2, carbonList[0].Length - i - 1);
    }
}

Console.WriteLine(oxygen * carbonDio);