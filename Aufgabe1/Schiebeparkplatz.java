public class Schiebeparkplatz
{
    String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";//Mit dem Alphabet kann die richtige Bezeichnung für das aktuelle Auto ermittelt werden.
    int verschobeneAutosRechts;
    int verschobeneAutosLinks;
    public Schiebeparkplatz(int beispieldatei)
    {
        List<QuerstehendesAuto> querAutos = new List<QuerstehendesAuto>();
        
        //Wählt die gewünschte Beispieldatei und führt das Programm an dieser aus.
        if(beispieldatei == 0)
        {
            QuerstehendesAuto hAuto0 = new QuerstehendesAuto("H", 2);
            QuerstehendesAuto iAuto0 = new QuerstehendesAuto("I", 5);
            querAutos.append(hAuto0);
            querAutos.append(iAuto0);
            verschieben(7, querAutos);
        }
        else if(beispieldatei == 1)
        {
            QuerstehendesAuto oAuto1 = new QuerstehendesAuto("O", 1);
            QuerstehendesAuto pAuto1 = new QuerstehendesAuto("P", 3);
            QuerstehendesAuto qAuto1 = new QuerstehendesAuto("Q", 6);
            QuerstehendesAuto rAuto1 = new QuerstehendesAuto("R", 10);
            querAutos.append(oAuto1);
            querAutos.append(pAuto1);
            querAutos.append(qAuto1);
            querAutos.append(rAuto1);
            verschieben(14, querAutos);
        }
        else if(beispieldatei == 2)
        {    
            QuerstehendesAuto oAuto2 = new QuerstehendesAuto("O", 2);
            QuerstehendesAuto pAuto2 = new QuerstehendesAuto("P", 5);
            QuerstehendesAuto qAuto2 = new QuerstehendesAuto("Q", 7);
            QuerstehendesAuto rAuto2 = new QuerstehendesAuto("R", 9);
            QuerstehendesAuto sAuto2 = new QuerstehendesAuto("S", 12);
            querAutos.append(oAuto2);
            querAutos.append(pAuto2);
            querAutos.append(qAuto2);
            querAutos.append(rAuto2);
            querAutos.append(sAuto2);
            verschieben(14, querAutos);
        }
        else if(beispieldatei == 3)
        {    
            QuerstehendesAuto oAuto3 = new QuerstehendesAuto("O", 1);
            QuerstehendesAuto pAuto3 = new QuerstehendesAuto("P", 4);
            QuerstehendesAuto qAuto3 = new QuerstehendesAuto("Q", 8);
            QuerstehendesAuto rAuto3 = new QuerstehendesAuto("R", 10);
            QuerstehendesAuto sAuto3 = new QuerstehendesAuto("S", 12);
            querAutos.append(oAuto3);
            querAutos.append(pAuto3);
            querAutos.append(qAuto3);
            querAutos.append(rAuto3);
            querAutos.append(sAuto3);
            verschieben(14, querAutos);
        }
        else if(beispieldatei == 4)
        {    
            QuerstehendesAuto qAuto4 = new QuerstehendesAuto("Q", 0);
            QuerstehendesAuto rAuto4 = new QuerstehendesAuto("R", 2);
            QuerstehendesAuto sAuto4 = new QuerstehendesAuto("S", 6);
            QuerstehendesAuto tAuto4 = new QuerstehendesAuto("T", 10);
            QuerstehendesAuto uAuto4 = new QuerstehendesAuto("U", 13);
            querAutos.append(qAuto4);
            querAutos.append(rAuto4);
            querAutos.append(sAuto4);
            querAutos.append(tAuto4);
            querAutos.append(uAuto4);
            verschieben(16, querAutos);
        }
        else if(beispieldatei == 5)
        {    
            QuerstehendesAuto pAuto5 = new QuerstehendesAuto("P", 2);
            QuerstehendesAuto qAuto5 = new QuerstehendesAuto("Q", 4);
            QuerstehendesAuto rAuto5 = new QuerstehendesAuto("R", 8);
            QuerstehendesAuto sAuto5 = new QuerstehendesAuto("S", 12);
            querAutos.append(pAuto5);
            querAutos.append(qAuto5);
            querAutos.append(rAuto5);
            querAutos.append(sAuto5);
            verschieben(15, querAutos);
        }
        else if(beispieldatei == 6)
        {
            QuerstehendesAuto dAuto6 = new QuerstehendesAuto("D", 1);
            querAutos.append(dAuto6);
            verschieben(3, querAutos);
        }
        else
        {
            System.out.println("Sie können nur eine Beispieldatei von 0-5 auswählen.");
        }        
    }

    //Gibt aus, ob und wie die quer stehenden Autos je geparktem Auto verschoben werden müssen, damit dieses heraus fahren kann.
    public void verschieben(int anzahlPlaetze, List<QuerstehendesAuto> querAutoListe)
    {
        String[] belegtePlaetze = erkenneBelegtePlaetze(anzahlPlaetze, querAutoListe);
        for(int i = 0; i < anzahlPlaetze; i++)
        {

            //Überprüft, ob überhaupt ein quer stehendes Auto vor dem aktuellen Auto steht. Falls nein, kann direkt ausgegeben werden, dass gar keine Verschiebung nötig ist.
            if(belegtePlaetze[i] == null)
            {
                System.out.println(alphabet.charAt(i) + ": benötigt keine Verschiebungen!");
            }
            
            
            else
            {
                boolean rechtsMoeglich = true;
                boolean linksMoeglich = true;
                verschobeneAutosRechts = 0;
                verschobeneAutosLinks = 0;
                String anleitungRechts = new String();
                String anleitungLinks = new String();
                
                //Versucht, die Verschiebungen entweder nach rechts oder links zu ermitteln. Falls eine Richtung nicht möglich ist, erfährt dies das Programm, denn dann wird eine NullPointerException geworfen. 
                try
                {
                    anleitungRechts = ermittleVerschiebungRechts(i, belegtePlaetze);
                }
                catch(Exception e)
                {
                    rechtsMoeglich = false;
                }
                
                try
                {
                    anleitungLinks = ermittleVerschiebungLinks(i, belegtePlaetze);
                }
                catch(Exception e)
                {
                    linksMoeglich = false;
                }
                                
                //Falls sowohl der rechte als auch der linke Weg möglich sind, wird der Weg, welcher die wenigsten Autos verschiebt ausgegeben.
                if(rechtsMoeglich && linksMoeglich)
                {
                    if(verschobeneAutosRechts > verschobeneAutosLinks)
                    {
                        System.out.println(alphabet.charAt(i) + ":" + anleitungLinks);
                    }
                    else
                    {
                        System.out.println(alphabet.charAt(i) + ":" + anleitungRechts);
                    }
                }
                //Falls nur ein Weg möglich ist, wird dieser ausgegeben.
                else if(rechtsMoeglich)
                {
                    System.out.println(alphabet.charAt(i) + ":" + anleitungRechts);
                }
                else if(linksMoeglich)
                {
                    System.out.println(alphabet.charAt(i) + ":" + anleitungLinks);
                }
                //Falls kein Weg möglich ist, wird man auch darüber in Kenntnis gesetzt
                else
                {
                    System.out.println(alphabet.charAt(i) + ": Leider gibt es keinen Weg, die quer stehenden Autos so zu verschieben, dass dieses Auto frei Kommt.");
                }
                
            }
        }
    }

    private String[] erkenneBelegtePlaetze(int anzahlPlaetze, List<QuerstehendesAuto> querAutoListe)
    {
        String[] blockierteWege = new String[anzahlPlaetze];
        if(querAutoListe != null)
        {
            querAutoListe.toFirst();
            while(querAutoListe.hasAccess())
            {
                int position = querAutoListe.getContent().getPosition();
                blockierteWege[position] = querAutoListe.getContent().getBezeichnung();
                blockierteWege[position + 1] = querAutoListe.getContent().getBezeichnung();
                querAutoListe.next();
            }
        }
        return blockierteWege;
    }
    
    private String ermittleVerschiebungRechts(int autoPosition, String[] belegtePlaetze)
    {
        if(belegtePlaetze[autoPosition] == null)
        {
            return "";
        }
        
        verschobeneAutosRechts++; //Da ein weiteres Auto zu verschieben ist, wird die Anzahl der verschobenen Autos erhöht.
        if(belegtePlaetze[autoPosition] == belegtePlaetze[autoPosition + 1]) //Prüft, ob der Rest des Autos rechts von der Autoposition ist.
        {
            return ermittleVerschiebungRechts(autoPosition + 2, belegtePlaetze) + ", " + belegtePlaetze[autoPosition] + " 1 rechts";
        }
        else //Da der Rest des Autos nicht rechts von der Autoposition war, muss dieser links von der Autoposition sein (es wird von einer Autolänge von 2 ausgegangen).
        {
            return ermittleVerschiebungRechts(autoPosition + 2, belegtePlaetze) + ", " + belegtePlaetze[autoPosition] + " 2 rechts";
        }
    }
    
    private String ermittleVerschiebungLinks(int autoPosition, String[] belegtePlaetze)
    {
        if(belegtePlaetze[autoPosition] == null)
        {
            return "";
        }
        
        verschobeneAutosLinks++; //Da ein weiteres Auto zu verschieben ist, wird die Anzahl der verschobenen Autos erhöht.
        if(belegtePlaetze[autoPosition] == belegtePlaetze[autoPosition - 1]) //Prüft, ob der Rest des Autos links von der Autoposition ist.
        {
            return ermittleVerschiebungLinks(autoPosition - 2, belegtePlaetze) + ", " + belegtePlaetze[autoPosition] + " 1 links";
        }
        else //Da der Rest des Autos nicht links von der Autoposition war, muss dieser rechts von der Autoposition sein (es wird von einer Autolänge von 2 ausgegangen).
        {
            return ermittleVerschiebungLinks(autoPosition - 2, belegtePlaetze) + ", " + belegtePlaetze[autoPosition] + " 2 links";
        }        
    }
}