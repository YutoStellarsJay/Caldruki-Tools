class Program
{
    static long SimilarScore(string value, string data)
    {
        long similar = 0;
        for (int i = 0; i < data.Length; i++)
            for (int j = 0; j < value.Length; j++)
            {
                if (value[j] == data[i])
                    similar++;
            }
        return similar;
    }
    struct Largest
    {
        public int index;
        public long value;
    }
    static string RandomSuprised()
    {
        switch (Random.Shared.Next(1, 6))
        {
            case 1:
                return "🤯";
            case 2:
                return "💀😱";
            case 3:
                return "😹";
            case 4:
                return "😂";
            case 5:
                return "🎉🥳";
        }
        return "";
    }
    static void Main()
    {
        string input;
        string[] toComp;
        if (File.Exists("worddb.csv"))
            toComp = File.ReadAllText("worddb.csv").Split(',');
        else
        {
            Console.WriteLine("Worddb.csv is needed to know prediction words!");
            return;
        }
        string Compare(string input)
        {
            Largest largest = new Largest()
            {
                index = 0,
                value = long.MinValue
            };
            for (int i = 0; i < toComp.Length; i++)
                if (SimilarScore(input, toComp[i]) > largest.value)
                {
                    largest.index = i;
                    largest.value = SimilarScore(input, toComp[i]);
                }
            return toComp[largest.index];
        }
        while (true)
        {
            Console.Write("Word: ");
            input = Console.ReadLine()!;
            Console.WriteLine(@$"{input}
backwards
{Compare(input)}{RandomSuprised()}");
        }
    }
}