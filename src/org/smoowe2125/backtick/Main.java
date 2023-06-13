package org.smoowe2125.backtick;

import java.io.File;
import java.io.FileNotFoundException;
import java.lang.*;
import java.util.Arrays;
import java.util.Scanner;

public class Main {

//    public static boolean checkSysLib(Object[] statements) {
//        boolean init = false;
//        for (int e = 0; e < statements.length; e++) {
//            if(statements[e].equals("import")) {
//                if(statements[e + 1].equals("syslib")) {
//                    init = true;
//                }
//            }
//        }
//        return init;
//    }
//
//    public static boolean checkSysIO(Object[] statements) {
//        boolean init = false;
//        for (int e = 0; e < statements.length; e++) {
//            if(statements[e].equals("import")) {
//                if(statements[e + 1].equals("sysio")) {
//                    init = true;
//                }
//            }
//        }
//        return init;
//    }

    public static void main(String[] args) throws Exception {
        SysLib syslib = new SysLib();
        SysIO sysio = new SysIO();
        Interpreter interpreter = new Interpreter();
        WordDivider divider = new WordDivider();
        Checker checker = new Checker();
        Scanner sc = new Scanner(System.in);
        if(args == null) {
            while (true) {
                System.out.print("backtick-shell $> ");
                String input = sc.nextLine();
                if (input.equals("quit") || input.equals("exit")) {
                    throw new Exception("Program was stopped by user!");
                }
                char[] inputS = input.toCharArray();
                Character[] iSplit = new Character[inputS.length];
                for (int k = 0; k < inputS.length; k++) {
                    iSplit[k] = inputS[k];
                }
                System.out.println(Arrays.toString(iSplit));
                //            divider.timesLetterDetected = 0;
                Object[] output = divider.divide(iSplit);
                Object[] statementOut = checker.scan(output);
                // Library stuff
            }
        } else {
            for (int i = 0; i < args.length; i++) {
                if(args[i].contains(".backtick")) {
                    try {
                        File script = new File(args[i]);
                        Scanner fileScan = new Scanner(script);
                        while (fileScan.hasNextLine()) {
                            divider.timesletterDetected = 0;
                            String line = fileScan.nextLine();
                            char[] lineSplit = line.toCharArray();
                            Character[] lnS = new Character[lineSplit.length];
                            for (int q = 0; q < lineSplit.length; q++) {
                                lnS[q] = lineSplit[q];
                            }
//                            System.out.println(Arrays.toString(lnS));
                            Object[] output = divider.divide(lnS);
                            Object[] statementOut = checker.scan(output);
                            // Library stuff
                            // For loop using while because why not
                            int e = 0;
                            while(e < statementOut.length) {
                                if(statementOut[e].equals("import")) {
                                    if(statementOut[e + 2].equals("syslib")) {
                                        syslib.initialize();
                                    } else if(statementOut[e + 2].equals("sysio")) {
                                        sysio.initialize();
                                    }
                                }
                                e++;
                            }
//                            System.out.println("SysLib Init: " + syslib.initialized);
//                            System.out.println("SysIO Init: " + sysio.initialized);

//                            sysio.println(Arrays.toString(statementOut));
                            interpreter.interpret(statementOut, syslib, sysio);
                        }
                        fileScan.close();
                    } catch (FileNotFoundException e) {
                        System.out.println("An error occured!");
                        e.printStackTrace();
                    }
                }
            }
        }
    }
}
