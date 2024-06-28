string? line;
StreamReader input = new ("input.txt");
line = input.ReadLine();
int[] destination = [0, 0];

while (line != null){
    string[] instruction = line.Split(" ");
    switch (instruction[0]){
        case "forward":
            destination[0] += Int32.Parse(instruction[1]);
            break;
        case "up":
            destination[1] -= Int32.Parse(instruction[1]);
            break;
        case "down":
            destination[1] += Int32.Parse(instruction[1]);
            break;
    }
    line = input.ReadLine();
}
input.Close();

Console.WriteLine(destination[0] * destination[1]);


input = new ("input.txt");
line = input.ReadLine();
destination = [0, 0];
int aim = 0;

while (line != null){
    string[] instruction = line.Split(" ");
    int num = Int32.Parse(instruction[1]);
    switch (instruction[0]){
        case "forward":
            destination[0] += num;
            destination[1] += num * aim;
            break;
        case "up":
            aim -= num;
            break;
        case "down":
            aim += num;
            break;
    }
    line = input.ReadLine();
}
input.Close();

Console.WriteLine(destination[0] * destination[1]);