package org.smoowe2125.backtick;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class WordDivider {

    public void println(Object obj) {
        System.out.println(obj);
    }
    public int timesletterDetected = 0;
    public String specialChars = "!@#%^&*()-=+[]{}:'|,./` ";

    public WordDivider() {
        // Does nothing
    }
        // You WILL find out why this code is commented out
//    public boolean letterDetected(List<Character> list, Character input) {
//        boolean letterDetect;
//        if (list.contains(input)) {
//            letterDetect = true;
//        } else {
//            letterDetect = false;
//        }
//        return letterDetect;
//    }
//    public int timesLetterDetected = 0;
//    public boolean detected = false;
    public String checkWords(Character[] input, int i) {
        // Check out my bad code commented here that was previously doing the same these uncommented lines do

//        Character[] letters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '"', '.'};
//        Character[] numbers = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0'};
//        List<Character> letterList = new ArrayList<>(Arrays.asList(letters));
//        List<Character> numList = new ArrayList<>(Arrays.asList(numbers));
        String aWord = "";

//        // Fuck it, I am going to use the same thing for word and number detection, and you can't do anything about it
//        if (timesLetterDetected == 0) {
//            if (letterDetected(letterList, input[i]) || letterDetected(numList, input[i])) {
//                detected = true;
//                timesLetterDetected++;
//                int q = 0;
//                String word = "";
//                try {
//                    while (letterDetected(letterList, input[i + q]) || letterDetected(numList, input[i + q])) {
//                        word += input[i + q];
//                        q++;
//                    }
//                } catch (Exception e) {
//                    q -= 1;
//                }
//                println(word);
//                aWord = word;
//            } else {
//                detected = false;
//            }
//        } else {
//            if (input[i].equals(' ') || input[i].equals('\n')) {
//                detected = false;
//                timesLetterDetected = 0;
//            }
//            if(input[i].equals(';')) {
//                aWord += ";";
//            } else if(input[i].equals('(')) {
//                aWord += "(";
//            } else if(input[i].equals(')')) {
//                aWord += ")";
//            }
//        }
        String letters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        String numbers = "1234567890";
        int q = 0;
        try {
            if(timesletterDetected == 0) {
                while (letters.contains(input[i + q].toString()) || numbers.contains(input[i + q].toString())) {
                    aWord += input[i + q];
                    q++;
                }
                timesletterDetected++;
                aWord += " ";
            }
        } catch (ArrayIndexOutOfBoundsException e) {
            q -= 1;
        }
        if(specialChars.contains(input[i].toString())) {
            aWord = input[i].toString();
            if(!input[i].equals(' ')) {
                aWord += " ";
            }
            timesletterDetected = 0;
        }

        return aWord;
    }

    public Object[] divide(Character[] input) {
        String wordSaver = "";
        for (int i = 0; i < input.length; i++) {
            wordSaver += checkWords(input, i);
        }
        String[] words = wordSaver.split(" ");
        ArrayList<Object> wordList = new ArrayList<>(Arrays.asList(words));
        for (int j = 0; j < wordList.size(); j++) {
            if(wordList.get(j).equals(" ")) {
                wordList.remove(j);
            }
        }
        Object[] wordsFinal = wordList.toArray();

        println(Arrays.toString(wordsFinal));

        return words;
    }
}
