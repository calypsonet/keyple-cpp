#pragma once

/**
     * Indicates the action to be taken after processing a SE.
     */
enum class PollingMode {
    /**
         * continue waiting for the insertion of a next SE.
         */
    REPEATING,
    /**
         * stop and wait for a restart signal.
         */
    SINGLESHOT
};