using System;
using System.IO;

namespace DFT
{
    class Program
    {
        const int HIGH_LEVEL = 5;
        const int LOW_LEVEL = 0;
        const double PI = 3.1416;
        const int N = 4096;

        struct ComplexNumber
        {
            public double Real;
            public double Imaginary;

            public ComplexNumber(double real, double imaginary)
            {
                Real = real;
                Imaginary = imaginary;
            }
        }

        static void Main(string[] args)
        {
            var timeSamples = new ComplexNumber[N];
            var freqSamples = new ComplexNumber[N];

            for (int i = 0; i < N; i++)
            {
                timeSamples[i].Real = (HIGH_LEVEL / ((double)N)) * i + LOW_LEVEL;
                timeSamples[i].Imaginary = 0;
            }

            freqSamples = CalcDFT(timeSamples);

            var sw = new StreamWriter("r.txt");
            for (int i = 0; i < N; i++)
            {
                sw.Write(freqSamples[i].Real + " " + freqSamples[i].Imaginary);
                if (i != N - 1)
                {
                    sw.WriteLine();
                }
            }
            sw.Close();

            //PrintComplexVector(freqSamples);
            //Console.ReadKey();
        }

        static ComplexNumber[] CalcDFT(ComplexNumber[] timeDomain)
        {
            var transform = new ComplexNumber[N];

            for (int i = 0; i < N; i++)
            {
                var sum = new ComplexNumber(0, 0);

                for (int j = 0; j < N; j++)
                {
                    ComplexNumber timeVal = timeDomain[j];

                    ComplexNumber twiddleFactor = ComplexExp(-2 * PI * j * i / N);

                    sum = ComplexAdd(sum, ComplexMult(timeVal, twiddleFactor));
                }

                transform[i] = sum;
            }

            return transform;
        }

        static ComplexNumber ComplexAdd(ComplexNumber n1, ComplexNumber n2)
        {
            ComplexNumber result;
            result.Real = n1.Real + n2.Real;
            result.Imaginary = n1.Imaginary + n2.Imaginary;

            return result;
        }

        static ComplexNumber ComplexMult(ComplexNumber n1, ComplexNumber n2)
        {
            ComplexNumber result;
            result.Real = (n1.Real * n2.Real) - (n1.Imaginary * n2.Imaginary);
            result.Imaginary = (n1.Real * n2.Imaginary) + (n1.Imaginary * n2.Real);

            return result;
        }

        static ComplexNumber ComplexExp(double exp)
        {
            ComplexNumber result;
            result.Real = Cosin(exp);
            result.Imaginary = Sin(exp);

            return result;
        }

        static double Sin(double n)
        {
            double result;
            double interm = n;

            result = interm;

            interm *= n * n;
            result -= interm / 6;

            interm *= n * n;
            result += interm / 120;

            interm *= n * n;
            result -= interm / 5040;

            interm *= n * n;
            result += interm / 362880;

            return result;
        }

        static double Cosin(double n)
        {
            double result;
            double interm = 1;

            result = interm;

            interm *= n * n;
            result -= interm / 2;

            interm *= n * n;
            result += interm / 24;

            interm *= n * n;
            result -= interm / 720;

            interm *= n * n;
            result += interm / 40320;

            return result;
        }

        static void PrintComplexVector(ComplexNumber[] complexVector)
        {
            for (int i = 0; i < N; i++)
            {
                Console.WriteLine("[" + i + "]: " + complexVector[i].Real + " + i*" + complexVector[i].Imaginary);
            }
        }
    }
}
