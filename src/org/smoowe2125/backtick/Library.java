package org.smoowe2125.backtick;

public class Library {
    protected String name;
    protected Object[] keywords;
    public boolean initialized = false;

    protected void setInitialized() {
        initialized = true;
    }
}
