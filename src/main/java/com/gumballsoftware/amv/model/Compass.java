package com.gumballsoftware.amv.model;

/**
 * Created by ktm on 2/3/15.
 */
public enum Compass {
    NORTH,
    SOUTH,
    EAST,
    WEST;

    static public Compass fromChar(char c) {
        Compass retval = WEST;

        switch (c) {
            case 'N':
            case 'n':
                retval = NORTH;
                break;
            case 'S':
            case 's':
                retval = SOUTH;
                break;
            case 'E':
            case 'e':
                retval = EAST;
                break;
        }
        return retval;
    }
}
