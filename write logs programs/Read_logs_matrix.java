package read_logs;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

public class Read_logs {

    public static void main(String[] args) throws Exception {
        String goldfilepath = "/home/grad/mcvieira/Desktop/goldMM.txt";
        
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
        
        String outfilepath = "out.log";
        int sdcIndex = 1;
        BufferedWriter bw = new BufferedWriter(new FileWriter(outfilepath));
        for(int folder_index = 1; folder_index < 8; folder_index++){
            String rfilepath = "/home/grad/mcvieira/Desktop/carol-fi/logs/mult-dup-random/sdcs-detected/2018_12_05/f"+folder_index+"/rMM.txt";
            bf = new BufferedReader(new FileReader(rfilepath));
            
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
                            bw.write("#SDC " + sdcIndex + "\n");
                            sdcIndex++;
                            foundDifferent = true;
                        }
                        bw.write("#ERR p: ["+i+","+j+"], r: "+matrix_r[i][j]+", e: "+matrix_gold[i][j]+"\n");
                    }
                }
            }
        }
        
        if(bw != null)
            bw.close();
    }
    
}
