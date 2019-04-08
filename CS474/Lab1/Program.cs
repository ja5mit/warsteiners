using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace Lab1
{
    class Program
    {
        static void Main(string[] args)
        {
            const int SIZE = 20; //constant integer of value 20
            int[] array = new int[SIZE]; //initializing an array of length SIZE

            Random r = new Random(); //declaring instance of random class

            for (int i = 0; i < SIZE; i++) //setting each element to a random number sequentially and displaying
            {
                array[i] = r.Next();
                Console.WriteLine(array[i]);
            }
            int largest = 0; //to store largest value

            Stopwatch MyTimer = new Stopwatch();
            MyTimer.Start();
            for (int i = 0; i < SIZE; i++) //sequentially finds the largest number 
            {
                if (array[i] > largest)
                {
                    largest = array[i];
                }
            }
            MyTimer.Stop();
            Console.WriteLine("\nThe largest number found sequentially is: " + largest); //display largest number
            Console.WriteLine("The time taken to find the largest number sequentially: " + MyTimer.Elapsed);
        }
    }
}

