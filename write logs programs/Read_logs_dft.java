package read_logs_fourier;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

public class Read_logs_fourier {

    public static void main(String[] args) throws Exception{
        String goldfilepath = "/home/grad/mcvieira/Desktop/goldDFT.txt";
        
        int size = 8192;
        
        double[][] freq_samples_r = new double[size][2];
        double[][] freq_samples_gold = new double[size][2];
        
        BufferedReader bf = new BufferedReader(new FileReader(goldfilepath));
        
        String line = "";
        String[] lineSplit;
        
        for(int i = 0; i < size; i++){
            line = bf.readLine();
            lineSplit = line.split(" ");
            
            for(int j = 0; j < 2; j++){
                freq_samples_gold[i][j] = Double.parseDouble(lineSplit[j]);
            }
        }
        
        String outfilepath = "outDFT.log";
        int sdcIndex = 1;
        BufferedWriter bw = new BufferedWriter(new FileWriter(outfilepath));
        for(int folder_index = 1; folder_index < 10; folder_index++){
            String rfilepath = "/home/grad/mcvieira/Desktop/carol-fi TESTE/logs/dft-random-dup/sdcs-detected/2018_12_07/f"+folder_index+"/rDFT.txt";
            bf = new BufferedReader(new FileReader(rfilepath));
            
            for(int i = 0; i < size; i++){
                line = bf.readLine();
                lineSplit = line.split(" ");
            
                for(int j = 0; j < 2; j++){
                    freq_samples_r[i][j] = Double.parseDouble(lineSplit[j]);
                }
            }
            
            boolean foundDifferent = false;
            
            for(int i = 0; i < size; i++){
                for(int j = 0; j < 2; j++){
                    if(freq_samples_r[i][j] != freq_samples_gold[i][j]){
                        if(foundDifferent == false){
                            bw.write("#SDC " + sdcIndex + "\n");
                            sdcIndex++;
                            foundDifferent = true;
                        }
                        bw.write("#ERR p: ["+i+","+j+"], r: "+freq_samples_r[i][j]+", e: "+freq_samples_gold[i][j]+"\n");
                    }
                }
            }
        }
        
        if(bw != null)
            bw.close();
    }
    
}
