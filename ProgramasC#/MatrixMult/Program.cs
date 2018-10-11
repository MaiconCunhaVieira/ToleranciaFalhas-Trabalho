using System;
using System.IO;

namespace MatrixMultiplicationDouble
{
    class Program
    {
        const int MATRIX_SIZE = 700;

        static void Main(string[] args)
        {
            var ma = new double[MATRIX_SIZE, MATRIX_SIZE];
            var mb = new double[MATRIX_SIZE, MATRIX_SIZE];
            var mr = new double[MATRIX_SIZE, MATRIX_SIZE];

            /*var rand = new Random();

            for(int row = 0; row < MATRIX_SIZE; row++)
            {
                for(int col = 0; col < MATRIX_SIZE; col++)
                {
                    int n1 = rand.Next(1, 100);
                    int n2 = rand.Next(1, 120);

                    ma[row, col] = Math.Round((double)n1 / (double)n2, 2);
                    mb[row, col] = Math.Round((double)n2 / (double)(n1 + n2), 2);
                }
            }*/

            ma = ReadMatrixFromFile("a.txt");
            mb = ReadMatrixFromFile("b.txt");

            //WriteMatrixToFile(ma, "a.txt");
            //WriteMatrixToFile(mb, "b.txt");

            mr = MultiplyMatrix(ma, mb);

            WriteMatrixToFile(mr, "r.txt");

            //PrintMatrix(ma);
            //PrintMatrix(mb);
            //PrintMatrix(mr);
            //Console.ReadKey();
        }

        static double[,] MultiplyMatrix(double[,] matrix_a, double[,] matrix_b)
        {
            var matrix_result = new double[MATRIX_SIZE, MATRIX_SIZE];

            for (int row = 0; row < MATRIX_SIZE; row++)
            {
                for (int col = 0; col < MATRIX_SIZE; col++)
                {
                    double sum = 0;

                    for (int k = 0; k < MATRIX_SIZE; k++)
                    {
                        sum += matrix_a[row, k] * matrix_b[k, col];
                    }

                    matrix_result[row, col] = Math.Round(sum, 4);
                }
            }

            return matrix_result;
        }

        static void PrintMatrix(double[,] matrix)
        {
            for (int row = 0; row < MATRIX_SIZE; row++)
            {
                Console.Write("[");
                for (int col = 0; col < MATRIX_SIZE; col++)
                {
                    Console.Write(matrix[row, col] + " ");
                }
                Console.WriteLine("]");
            }
            Console.WriteLine();
        }

        static void WriteMatrixToFile(double[,] matrix, string filename)
        {
            var tw = new StreamWriter(filename);

            for (int i = 0; i < MATRIX_SIZE; i++)
            {
                for (int j = 0; j < MATRIX_SIZE; j++)
                {
                    tw.Write(matrix[i, j] + " ");
                }
                if (i != MATRIX_SIZE - 1)
                {
                    tw.WriteLine();
                }
            }

            tw.Close();
        }

        static double[,] ReadMatrixFromFile(string filename)
        {
            var matrix = new double[MATRIX_SIZE, MATRIX_SIZE];
            var tr = new StreamReader(filename);
            var file = tr.ReadToEnd();

            int i = 0;
            foreach (var row in file.Split('\n'))
            {
                int j = 0;
                foreach (var col in row.Trim().Split(' '))
                {
                    matrix[i, j] = double.Parse(col.Trim());
                    j++;
                }
                i++;
            }

            tr.Close();

            return matrix;
        }
    }
}
