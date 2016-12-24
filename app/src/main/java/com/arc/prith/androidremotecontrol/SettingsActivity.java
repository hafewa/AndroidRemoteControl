package com.arc.prith.androidremotecontrol;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.TextWatcher;
import android.text.method.ScrollingMovementMethod;
import android.view.View;
import android.widget.EditText;
import android.widget.ScrollView;
import android.widget.TextView;
import android.widget.Toast;

public class SettingsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        ScrollView rl = (ScrollView) findViewById(R.id.layout_Log);
        rl.setVisibility(View.INVISIBLE);

        //set the scroll method of the log textview
        TextView tv = (TextView) findViewById(R.id.lbl_Log);
        tv.setMovementMethod(new ScrollingMovementMethod());

        initialize();
    }

    public void btn_ShowLog_OnClick(View v)
    {
        ScrollView rl = (ScrollView) findViewById(R.id.layout_Settings);
        rl.setVisibility(View.INVISIBLE);

        TextView tv = (TextView) findViewById(R.id.lbl_Log);
        tv.setText(getLog());

        rl = (ScrollView) findViewById(R.id.layout_Log);
        rl.setVisibility(View.VISIBLE);

    }

    public void btn_ClearLog_OnClick(View v)
    {
        clearLog();

        TextView tv = (TextView) findViewById(R.id.lbl_Log);
        tv.setText(getLog());
    }

    public void btn_Back_OnClick(View v)
    {
        ScrollView rl = (ScrollView) findViewById(R.id.layout_Settings);
        rl.setVisibility(View.VISIBLE);

        rl = (ScrollView) findViewById(R.id.layout_Log);
        rl.setVisibility(View.INVISIBLE);
    }

    public void btn_Save_OnClick(View v)
    {
        if(!mTextChanged)
        {
            return;
        }

        final int vid1ID = Integer.parseInt(getText(R.string.vid1ID).toString());
        final int vid2ID = Integer.parseInt(getText(R.string.vid2ID).toString());
        final int vid3ID = Integer.parseInt(getText(R.string.vid3ID).toString());

        try {

            EditText et = (EditText) findViewById(R.id.txt_StartCmd);
            setStartCommandString(et.getText().toString());

            et = (EditText) findViewById(R.id.txt_StopCmd);
            setStopCommandString(et.getText().toString());

            et = (EditText) findViewById(R.id.txt_Vid1Name);
            setVideoName(vid1ID, et.getText().toString());

            et = (EditText) findViewById(R.id.txt_Vid2Name);
            setVideoName(vid2ID, et.getText().toString());

            et = (EditText) findViewById(R.id.txt_Vid3Name);
            setVideoName(vid3ID, et.getText().toString());

            et = (EditText) findViewById(R.id.txt_Vid1Delay);
            setVideoDelay(vid1ID, Integer.parseInt(et.getText().toString()));

            et = (EditText) findViewById(R.id.txt_Vid2Delay);
            setVideoDelay(vid2ID, Integer.parseInt(et.getText().toString()));

            et = (EditText) findViewById(R.id.txt_Vid3Delay);
            setVideoDelay(vid3ID, Integer.parseInt(et.getText().toString()));

            et = (EditText) findViewById(R.id.txt_IPAddr);
            setHostIpAddress(et.getText().toString());

            et = (EditText) findViewById(R.id.txt_Port);
            setHostPortNumber(Integer.parseInt(et.getText().toString()));

            savePersistentData();

            Toast.makeText(this, "Data Saved Successfully", Toast.LENGTH_SHORT).show();
            (findViewById(R.id.btn_Save)).setEnabled(false);
        }
        catch(Exception e)
        {
            Toast.makeText(this, "ERROR in saving data!", Toast.LENGTH_SHORT).show();
        }
    }

    public void data_Changed()
    {
        mTextChanged = true;
        (findViewById(R.id.btn_Save)).setEnabled(true);
    }

    public void btn_Cancel_OnClick(View v)
    {
        returnToUserInterface();
    }

    private void returnToUserInterface()
    {
        Intent intent = new Intent(this, MainActivity.class);
        startActivity(intent);
        finish();
    }

    private void initialize()
    {
        fillFormData();

        //focus on the first EditText
        EditText et = (EditText) findViewById(R.id.txt_StartCmd);
        et.requestFocus();

        mTextChanged = false;

        // create a textwatcher for all the settings elements
        TextWatcher tw = new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence s, int start, int count, int after) {}

            @Override
            public void onTextChanged(CharSequence s, int start, int before, int count) {}

            @Override
            public void afterTextChanged(Editable s) {
                data_Changed();
            }
        };

        et.addTextChangedListener(tw);

        et = (EditText) findViewById(R.id.txt_StopCmd);
        et.addTextChangedListener(tw);

        et = (EditText) findViewById(R.id.txt_Vid1Name);
        et.addTextChangedListener(tw);

        et = (EditText) findViewById(R.id.txt_Vid2Name);
        et.addTextChangedListener(tw);

        et = (EditText) findViewById(R.id.txt_Vid3Name);
        et.addTextChangedListener(tw);

        et = (EditText) findViewById(R.id.txt_IPAddr);
        et.addTextChangedListener(tw);

        et = (EditText) findViewById(R.id.txt_Port);
        et.addTextChangedListener(tw);

        et = (EditText) findViewById(R.id.txt_Vid1Delay);
        et.addTextChangedListener(tw);

        et = (EditText) findViewById(R.id.txt_Vid2Delay);
        et.addTextChangedListener(tw);

        et = (EditText) findViewById(R.id.txt_Vid3Delay);
        et.addTextChangedListener(tw);

        (findViewById(R.id.btn_Save)).setEnabled(false);
    }

    private void fillFormData()
    {
        final int vid1ID = Integer.parseInt(getText(R.string.vid1ID).toString());
        final int vid2ID = Integer.parseInt(getText(R.string.vid2ID).toString());
        final int vid3ID = Integer.parseInt(getText(R.string.vid3ID).toString());

        EditText et = (EditText) findViewById(R.id.txt_StartCmd);
        et.setText(getStartCommandString());

        et = (EditText) findViewById(R.id.txt_StopCmd);
        et.setText(getStopCommandString());

        et = (EditText) findViewById(R.id.txt_Vid1Name);
        et.setText(getVideoName(vid1ID));

        et = (EditText) findViewById(R.id.txt_Vid2Name);
        et.setText(getVideoName(vid2ID));

        et = (EditText) findViewById(R.id.txt_Vid3Name);
        et.setText(getVideoName(vid3ID));

        et = (EditText) findViewById(R.id.txt_Vid1Delay);
        et.setText(String.valueOf( getVideoDelay(vid1ID)));

        et = (EditText) findViewById(R.id.txt_Vid2Delay);
        et.setText(String.valueOf(getVideoDelay(vid2ID)));

        et = (EditText) findViewById(R.id.txt_Vid3Delay);
        et.setText(String.valueOf(getVideoDelay(vid3ID)));

        et = (EditText) findViewById(R.id.txt_IPAddr);
        et.setText(getHostIpAddress());

        et = (EditText) findViewById(R.id.txt_Port);
        et.setText(String.valueOf(getHostPortNumber()));
    }

    public native String getStartCommandString();
    public native String getStopCommandString();
    public native String getVideoName(int id);
    public native int getVideoDelay(int id);
    public native String getHostIpAddress();
    public native int getHostPortNumber();


    public native void setStartCommandString(String cmd);
    public native void setStopCommandString(String cmd);
    public native void setVideoName(int id, String name);
    public native void setVideoDelay(int id, int delayInMs);
    public native void setHostIpAddress(String address);
    public native void setHostPortNumber(int port);
    public native String getLog();
    public native void clearLog();
    public native void savePersistentData();


    private boolean mTextChanged;

}
