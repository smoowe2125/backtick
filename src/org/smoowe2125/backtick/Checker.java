package org.smoowe2125.backtick;

public class Checker {

    private Object check(Object[] input, int i) {
        SysLib sysLib = new SysLib();
        SysIO sysio = new SysIO();
        String statement = "";
        if(!input[i].equals(" ")) {
            statement += input[i];
            statement += " ";
        }
        // The user can extend the possibilities by making their own libraries and including the check for their keywords and stuff here
        System.out.println("Statement: " + statement);
        return statement;
    }
    public Object[] scan(Object[] input) {
        Object[] statements = new Object[]{};
        String statementSaver = "";
        for (int i = 0; i < input.length; i++) {
            statementSaver += check(input, i);
        }
        statements = statementSaver.split(" ");
        return statements;
    }
}
