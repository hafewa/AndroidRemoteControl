package com.arc.prith.androidremotecontrol;

import android.content.res.Resources;
import android.support.test.InstrumentationRegistry;
import android.support.test.espresso.assertion.ViewAssertions;
import android.support.test.rule.ActivityTestRule;

import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;

import static android.support.test.espresso.Espresso.onView;
import static android.support.test.espresso.action.ViewActions.click;
import static android.support.test.espresso.action.ViewActions.closeSoftKeyboard;
import static android.support.test.espresso.action.ViewActions.scrollTo;
import static android.support.test.espresso.action.ViewActions.typeText;
import static android.support.test.espresso.assertion.ViewAssertions.matches;
import static android.support.test.espresso.matcher.ViewMatchers.isCompletelyDisplayed;
import static android.support.test.espresso.matcher.ViewMatchers.withId;
import static android.support.test.espresso.matcher.ViewMatchers.withText;
import static org.hamcrest.core.IsNot.not;

/**
 * Created by prith on 12/23/2016.
 */
public class MainActivityTest {

    private String mLogin;
    private String mPassword;


    @Rule
    public ActivityTestRule<MainActivity> mActivityRule = new ActivityTestRule<>(
            MainActivity.class);

    @Before
    public void initValidStringLogin() {

        Resources resources = InstrumentationRegistry.getContext().getResources();
        mPassword = "password";

        mLogin = "admin";
    }

    @Test
    public void criticalPath() throws Exception {

        // on the main screen check whether all the 4 buttons are visible
        onView(withId(R.id.btn_RevealAdminCredentials)).check(matches(isCompletelyDisplayed()));
        onView(withId(R.id.btn_Vid1)).check(matches(isCompletelyDisplayed()));
        onView(withId(R.id.btn_Vid2)).check(matches(isCompletelyDisplayed()));
        onView(withId(R.id.btn_Vid3)).check(matches(isCompletelyDisplayed()));

        //open the admin login layout
        onView(withId(R.id.btn_RevealAdminCredentials)).perform(click());

        //check whether all the elements of the admin layout is available
        onView(withId(R.id.txt_loginID)).check(matches(isCompletelyDisplayed()));
        onView(withId(R.id.txt_Password)).check(matches(isCompletelyDisplayed()));
        onView(withId(R.id.btn_AdminLogIn)).check(matches(isCompletelyDisplayed()));
        onView(withId(R.id.btn_BackToUserInterface)).check(matches(isCompletelyDisplayed()));

        //type the credentials
        onView(withId(R.id.txt_loginID)).perform(typeText(mLogin));
        onView(withId(R.id.txt_Password)).perform(typeText(mPassword), closeSoftKeyboard());

        //login
        onView(withId(R.id.btn_AdminLogIn)).perform(click());

        // check whether the settings screen is loaded properly
        onView(withId(R.id.btn_Cancel)).check(matches(isCompletelyDisplayed()));

        // go to show log layout
        onView(withId(R.id.txt_StartCmd)).perform(closeSoftKeyboard());
        onView(withId(R.id.btn_ShowLog)).perform(scrollTo(), click());

        //check whether all the buttons are visible
        onView(withId(R.id.btn_ToSettings)).check(matches(isCompletelyDisplayed()));
        onView(withId(R.id.btn_ClearLog)).check(matches(isCompletelyDisplayed()));

        onView(withId(R.id.btn_ClearLog)).perform(click());
        onView(withId(R.id.lbl_Log)).check(matches(withText(" ")));
        onView(withId(R.id.btn_ToSettings)).perform(click());
    }

    @Test
    public void logCheck() throws Exception {
        //open the admin login layout
        onView(withId(R.id.btn_Vid1)).perform(click());
        onView(withId(R.id.btn_Vid2)).perform(click());
        onView(withId(R.id.btn_Vid3)).perform(click());
        onView(withId(R.id.btn_RevealAdminCredentials)).perform(click());

        //type the credentials
        onView(withId(R.id.txt_loginID)).perform(typeText(mLogin));
        onView(withId(R.id.txt_Password)).perform(typeText(mPassword), closeSoftKeyboard());

        //login
        onView(withId(R.id.btn_AdminLogIn)).perform(click());

        // go to show log layout
        onView(withId(R.id.txt_StartCmd)).perform(closeSoftKeyboard());
        onView(withId(R.id.btn_ShowLog)).perform(scrollTo(),click());

        //since we clicked on some buttons, the log should not be empty
        onView(withId(R.id.lbl_Log)).check(matches(not(withText(""))));

        onView(withId(R.id.btn_ClearLog)).perform(click());

        //the clear log button should empty the log
        onView(withId(R.id.lbl_Log)).check(matches(withText(" ")));
    }

}