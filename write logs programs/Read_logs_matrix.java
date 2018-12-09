package read_logs;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

public class Read_logs {

    public static void main(String[] args) throws Exception {
        String goldfilepath = "C:\\Users\\Maicon\\Desktop\\goldMM.txt";

        int size = 600;

        double[][] matrix_r = new double[size][size];
        double[][] matrix_gold = new double[size][size];

        BufferedReader bf = new BufferedReader(new FileReader(goldfilepath));

        String line = "";
        String[] lineSplit;

        for(int i = 0; i < size; i++){
            line = bf.readLine();
            lineSplit = line.split(" ");

            for(int j = 0; j < size; j++){
                matrix_gold[i][j] = Double.parseDouble(lineSplit[j]);
            }
        }

        String outfilepath = "mm-errors.log";
        int sdcIndex = 1;
        BufferedWriter bw = new BufferedWriter(new FileWriter(outfilepath));
        for(int folder_index = 1; folder_index <= 256; folder_index++){
            if(true){
                String rfilepath = "H:\\logs\\mult-random-dup\\mult-dup-random1\\sdcs-detected\\2018_12_05\\f ("+folder_index+")\\rMM.txt";
                bf = new BufferedReader(new FileReader(rfilepath));

                //System.out.println(folder_index);
                for(int i = 0; i < size; i++){
                    line = bf.readLine();
                    lineSplit = line.split(" ");

                    for(int j = 0; j < size; j++){
                        matrix_r[i][j] = Double.parseDouble(lineSplit[j]);
                    }
                }

                boolean foundDifferent = false;

                for(int i = 0; i < size; i++){
                    for(int j = 0; j < size; j++){
                        if(matrix_r[i][j] != matrix_gold[i][j]){
                            if(foundDifferent == false){
                                //System.out.println("achou diferente!");
                                bw.write("#SDC " + sdcIndex + "\n");
                                sdcIndex++;
                                foundDifferent = true;
                            }
                            bw.write("#ERR p: ["+i+","+j+"], r: "+matrix_r[i][j]+", e: "+matrix_gold[i][j]+"\n");
                        }
                    }
                }
            }

        }

        if(bw != null)
            bw.close();
    }
    
}
