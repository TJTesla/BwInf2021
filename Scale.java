import java.util.ArrayList;
import java.util.Collections;
import java.util.Scanner;

public class Scale {

    private ArrayList<Integer> weights;//Werte in g
    private Scanner scanner;
    private String scannerInput;

    public static void main(String[] args) {
        new Scale();
    }

    public Scale() {
        weights = new ArrayList<>();
        scanner = new Scanner(System.in);
        scannerInput = scanner.next();
        while (!scannerInput.equalsIgnoreCase("done")) {
            addWeight(Integer.parseInt(scannerInput));
            scannerInput = scanner.next();
        }
        weights.add(10);
        weights.add(10);
        weights.add(10);
        weights.add(50);
        weights.add(50);
        weights.add(100);
        weights.add(100);
        weights.add(100);
        weights.add(500);
        weights.add(500);
        weights.add(500);
        weights.add(1000);
        weights.add(1000);
        weights.add(1000);
        weights.add(5000);
        Collections.sort(weights);//sortieren von klein nach groß
        System.out.println("Gewichtsliste:");
        for (int weight : weights)
            System.out.println("Gewicht: " + weight);
        check();
    }

    /*
    Gewichtsstück hinzufügen
     */
    private void addWeight(int weightInGram) {
        weights.add(weightInGram);
    }

    /*
    Rechnungen
     */
    private void check() {
        for (int i = 10; i <= 10000; i += 10) {//i = Sack, von 10 Gramm bis 10 Kg
            for (int j = 0; j < weights.size() - 1; j++) {//j = Gewichts-Index der Liste
                if (i == weights.get(j)) {//Sack = Gewicht
                    System.out.println(i + " Gramm schwerer Sack auf der linken Seite und " + weights.get(j) + " Gramm schweres Gewicht auf der rechten Seite\n");
                    break;
                } else if (i < weights.get(j)) {//Sack < Gewicht
                    System.out.println(i + " Gramm schwerer Sack ist leichter als " + weights.get(j) + " Gramm schweres Gewicht");
                    checkWithAddWeights(i, j);
                    break;
                }
            }
        }
    }

    private void checkWithAddWeights(int weight, int index) {
        if (!addLowerWeight(weight, index)) {//weight = Sack, index = Gewichts-Index der Liste (schwerer als der Sack)
            if (!addHigherWeight(weight, index)) {//weight = Sack, index = Gewichts-Index der Liste (schwerer als der Sack)
                System.out.println("Nährung an " + weight);
            }
        }
    }

    private boolean addLowerWeight(int weight, int index) {//weight = Gewicht, index = Gewichts-Index der Liste (schwerer als der Sack)
        for (int i = 0; i < weights.size() - 1; i++) {//i = Gewichts-Index der Liste
            int newWeight = weights.get(index - 1) + weights.get(i);//Die Gewichte auf der rechten Seite
            if (weight == newWeight) {//Sack = Gewichte
                System.out.println(weight + " Gramm schwerer Sack auf der linken Seite und " + weights.get(index - 1) + " und " + weights.get(i) + " Gramm schweres Gewicht auf der rechten Seite\n");
                return true;
            } else if (weight < newWeight) {//Sack < Gewichte
                System.out.println(weight + " Gramm ist leichter als " + newWeight + " Gramm schweres Gewicht");
                if (i != 0) {
                    return addLowerWeight1(weight, weights.get(index - 1), i);
                } else {
                    return false;
                }
            }
        }
        return false;
    }

    private boolean addLowerWeight1(int weight, int minWeight, int add1) {
        for (int i = 0; i < weights.size() - 1; i++) {//i = Gewichts-Index der Liste
            if (i != add1) {//Nicht das gleiche Gewicht
                int newWeight = weights.get(i) + minWeight + weights.get(add1);//Die Gewichte auf der rechten Seite
                if (weight == newWeight) {//Sack = Gewichte
                    System.out.println(weight + " Gramm schwerer Sack auf der linken Seite und " + minWeight + ", " + weights.get(add1 - 1) + " und " + weights.get(i) + " Gramm schweres Gewicht auf der rechten Seite\n");
                    return true;
                } else if (weight < newWeight) {//Sack < Gewichte
                    if (i != 0) {
                        return addLowerWeight2(weight, minWeight, add1, i);
                    } else {
                        return false;
                    }
                }
            }
        }
        return false;
    }

    private boolean addLowerWeight2(int weight, int minWeight, int add1, int add2) {
        for (int i = 0; i < weights.size() - 1; i++) {//i = Gewichts-Index der Liste
            if (i != add1 && i != add2) {//Nicht das gleiche Gewicht
                int newWeight = weights.get(i) + minWeight + weights.get(add1) + weights.get(add2);//Die Gewichte auf der rechten Seite
                if (weight == newWeight) {//Sack = Gewichte
                    System.out.println(weight + " Gramm schwerer Sack auf der linken Seite und " + minWeight + ", " + weights.get(i) + ", " + weights.get(add1) + " und " + weights.get(add2) + " Gramm schweres Gewicht auf der reechten Seite\n");
                    return true;
                } else if (weight < newWeight) {//Sack < Gewichte
                    if (i != 0) {
                        return addLowerWeight3(weight, minWeight, add1, add2, i);
                    } else {
                        return false;
                    }
                }
            }
        }
        return false;
    }

    private boolean addLowerWeight3(int weight, int minWeight, int add1, int add2, int add3) {
        for (int i = 0; i < weights.size() - 1; i++) {//i = Gewichts-Index der Liste
            if (i != add1 && i != add2 && i != add3) {//Nicht das gleiche Gewicht
                int newWeight = weights.get(i) + minWeight + weights.get(add1) + weights.get(add2) + weights.get(add3);//Die Gewichte auf der rechten Seite
                if (weight == newWeight) {//Sack = Gewichte
                    System.out.println(weight + " Gramm schwerer Sack auf der linken Seite und " + minWeight + ", " + weights.get(i) + ", " + weights.get(add1) + ", " + weights.get(add2) + " und " + weights.get(add3) + " Gramm schweres Gewicht auf der reechten Seite\n");
                    return true;
                } else if (weight < newWeight) {//Sack < Gewichte
                    return false;
                }
            }
        }
        return false;
    }

    /*private boolean addLowerWeights(int weight, int index) {
        ArrayList<Integer> zusatzGewichte = new ArrayList<>();
        for (int a = 0; a <= 5; a++) {
            for (int i = 0; i < weights.size() - 1; i++) {//i = Gewichts-Index der Liste
                int newWeight = weights.get(index - 1) + weights.get(i);//Die Gewichte auf der rechten Seite
                for (int gewicht : zusatzGewichte){
                   newWeight += gewicht;
                }
                if (weight == newWeight) {//Sack = Gewichte
                    System.out.println(weight + " Gramm schwerer Sack auf der linken Seite und " + weights.get(index - 1) + " und " + weights.get(i) + " Gramm schweres Gewicht auf der rechten Seite\n");
                    return true;
                } else if (weight < newWeight) {//Sack < Gewichte
                    System.out.println(weight + " Gramm ist leichter als " + newWeight + " Gramm schweres Gewicht");
                    zusatzGewichte.add(i);
                }
            }
        }
        return false;
    }*/

    private boolean addHigherWeight(int weight, int higherIndex) {
        int max = weights.get(higherIndex);//Die Gewichte auf der rechten Seite
        for (int i = 0; i < weights.size() - 1; i++) {//i = Gewichts-Index der Liste
            int newSack = weight + weights.get(i);
            if (newSack == max) {//Sack + Gewicht = Gewicht
                System.out.println(weight + " Gramm schwerer Sack und " + weights.get(i) + " Gramm schweres Gewicht auf der linken Seite und " + max + " Gramm schweres Gewicht auf der rechten Seite\n");
                return true;
            } else if (newSack < max) {//Sack + Gewicht < Gewicht
                System.out.println(weight + " Gramm schwerer Sack und " + weights.get(i) + " Gramm schweres Gewicht sind leichter als " + max + " Gramm schweres Gewicht");
                if (i != 0) {
                    return addHigherWeight1(weight, higherIndex, i);
                }

            }
        }
        return false;
    }

    private boolean addHigherWeight1(int weight, int higherIndex, int add1) {
        int max = weights.get(higherIndex);//Die Gewichte auf der rechten Seite
        for (int i = 0; i < weights.size() - 1; i++) {//i = Gewichts-Index der Liste
            if (i != add1) {
                int newSack = weight + weights.get(add1) + weights.get(i);
                if (newSack == max) {//Sack + Gewicht = Gewicht
                    System.out.println(weight + " Gramm schwerer Sack, " + weights.get(add1) + " und " + weights.get(i) + " Gramm schweres Gewicht auf der linken Seite und " + max + " Gramm schweres Gewicht auf der rechten Seite\n");
                    return true;
                } else if (newSack < max) {//Sack + Gewicht < Gewicht
                    System.out.println(weight + " Gramm schwerer Sack, " + weights.get(add1) + " und " + weights.get(i) + " Gramm schweres Gewicht sind leichter als " + max + " Gramm schweres Gewicht");
                    return false;
                }
            }
        }
        return false;
    }
}