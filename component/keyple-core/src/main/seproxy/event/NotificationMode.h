#pragma once
/**
     * The NotificationMode defines the expected behavior when processing a
     * default selection.
     */
enum class NotificationMode {
    /**
         * All SEs presented to readers are notified regardless of the result of
         * the default
         * selection.
         */
    ALWAYS,

    /**
         * Only SEs that have been successfully selected (logical channel open)
         * will be notified. The others will be ignored and the application will
         * not be aware of them.
         */
    MATCHED_ONLY
};