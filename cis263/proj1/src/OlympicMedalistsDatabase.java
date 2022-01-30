
import java.util.ArrayList;
import java.io.*;
import java.util.*;
import java.util.stream.Collectors;
public class OlympicMedalistsDatabase 
{
    private ArrayList < OlympicMedalist > om;
    private ArrayList < OlympicCountryMedals > ocm;

    public OlympicMedalistsDatabase() {
        om = new ArrayList < OlympicMedalist > ();
        ocm = new ArrayList < OlympicCountryMedals > ();
    }

    public void readOlympicMedalistData(String filename) {
        // Read the full set of data from a text file
        try{
            // open the text file and use a Scanner to read the text
            FileInputStream fileByteStream = new FileInputStream(filename);
            Scanner scnr = new Scanner(fileByteStream);
            scnr.nextLine(); // reads the column headers

            // keep reading as long as there is more data
            while(scnr.hasNext()) {
                // reads each record of the file
                String data = scnr.nextLine();
                OlympicMedalist olympicMedalist = new OlympicMedalist(data);
                om.add(olympicMedalist);
            }
            generateCountryTotalMedals(); 
            fileByteStream.close();

            scnr.close();
        }
        catch(IOException e) {
            System.out.println("Failed to read the data file: " + filename);        }

        // for(OlympicMedalist olimpico : om){
        //     System.out.println(olimpico);
        // }

        
    }

    public void generateCountryTotalMedals() {
        // Insert your code here

        TreeMap<String, int[]> totals= new TreeMap<String, int[]>();

        for(int i =0; i < om.size();i++){
            String key = om.get(i).getCity() + "," +om.get(i).getYear() + "," + om.get(i).getCountryCode();
            int[] medals = new int[3];
            if(totals.containsKey(key)){
                
                // Retrieve into an array of integers (medals) the current value of the array stored in totals
                medals = totals.get(key);
                
                if(om.get(i).getMedal().equals("Gold")){
                    medals[0]+=1;
                }
                if(om.get(i).getMedal().equals("Silver")){
                    medals[1]+=1;
                }
                if(om.get(i).getMedal().equals("Bronze")){
                    medals[2]+=1;
                }
                totals.put(key,medals);

                
                

                // for(int j =0; j<medals.length;j++){
                //     System.out.println(medals[j]);
                // }
                
            }else{
                
                if(om.get(i).getMedal().equals("Gold")){
                    medals[0]+=1;
                }
                if(om.get(i).getMedal().equals("Silver")){
                    medals[1]+=1;
                }
                if(om.get(i).getMedal().equals("Bronze")){
                    medals[2]+=1;
                }
                
            }
            totals.put(key,medals);

        }

        for(Map.Entry<String,int[]>entry : totals.entrySet()){
            // System.out.println(entry.getKey()+ " " + entry.getValue()[0]); 

            String[] separated = entry.getKey().split(",");
           
            OlympicCountryMedals temp = new OlympicCountryMedals(Integer.parseInt(separated[1]), separated[0], separated[2], entry.getValue()[0], entry.getValue()[1], entry.getValue()[2]);
            ocm.add(temp);
        }
        for(OlympicCountryMedals pais : ocm){
            System.out.println(pais);
        }
    }

    public int countAllMedalists() {
        // return 100;
        System.out.println(om.size());
        return om.size();
        
    }

    public int countAllWomen() {
        int count = 0;
        for(OlympicMedalist o : om) {
            if (o.getGender().equals("Women")) {
                count++;
            }
        }
        return count;
    }

    public int countAllMen() {
        int count = 0;
        for(OlympicMedalist o : om) {
            if (o.getGender().equals("Men")) {
                count++;
            }
        }
        return count;
    }

    public ArrayList < OlympicMedalist > getMedalistsDatabase() {
        return om;
    }

    public ArrayList < OlympicCountryMedals > getCountryTotalMedalsDatabase() {
        return ocm;
    }

    public ArrayList < OlympicMedalist > searchMedalistsByYear(int year) {
        ArrayList < OlympicMedalist > result = 
            new ArrayList < OlympicMedalist >();
        for(OlympicMedalist o : om) {
            if (o.getYear() == year) {
                result.add(o);
            }
        }
        return result;
    }

    public ArrayList < OlympicMedalist > searchMedalistsByCountry
    (String country) {
        ArrayList < OlympicMedalist > result = 
            new ArrayList < OlympicMedalist >();
        for(OlympicMedalist o : om) {
            if (o.getCountryCode().equals(country)) {
                result.add(o);
            }
        }
        return result;
    }

    public  OlympicMedalist  findAthlete    (String name) {
        OlympicMedalist result = null;
        for(OlympicMedalist o : om) {
            if (o.getName().equalsIgnoreCase(name)) {
                result = o;
            }
        }
        return result;
    }

    public ArrayList < OlympicCountryMedals > searchCountryMedalsByYear(int year) {
        ArrayList < OlympicCountryMedals > result = 
            new ArrayList < OlympicCountryMedals >();
        for(OlympicCountryMedals o : ocm) {
            if (o.getYear() == year) {
                result.add(o);
            }
        }
        return result;
    }

    public ArrayList < OlympicCountryMedals > topTenCountriesGoldMedals(int year) {
       
        ArrayList < OlympicCountryMedals > result = new ArrayList < OlympicCountryMedals >();
        // Add your code here
        
        for(int i=0; i < ocm.size();i++){
            if(year==ocm.get(i).getYear()){
                result.add(ocm.get(i));
            }
        }
        Collections.sort(result);

        if(result.size()>=10){
        
            List<OlympicCountryMedals> lista =result.subList(0, 10);
            ArrayList <OlympicCountryMedals> conver =new ArrayList<OlympicCountryMedals>(lista);
            return conver; 
        }
        return result;



        
    }
    public String findCountryWithHighestBronzeMedalsByYear(int year)
    {
        // One implementation:
        // String result = null;
        // int highestMedalCountSoFar = 0;
        // for (OlympicCountryMedals o : ocm) {
        // if (o.getYear() == year) {
        // if (o.getBronzeMedals() > highestMedalCountSoFar) {
        // result = o.getCountryCode();
        // highestMedalCountSoFar = o.getBronzeMedals();
        // }
        // }
        // }
        // return result;
        // A second implementation:
        ArrayList < OlympicCountryMedals > filteredByYear =          
        ocm.stream().filter(s -> s.getYear() == year).
        collect(Collectors.toCollection(ArrayList::new));
        if (filteredByYear.size() != 0) {
            OlympicCountryMedals r = Collections.max(filteredByYear,
                    Comparator.comparing(o->o.getBronzeMedals()));
            return r.getCountryCode();
        }
        else {
            return null;
        }

    }
}
