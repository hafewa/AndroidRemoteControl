package com.arc.prith.androidremotecontrol;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class SettingsActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);

        initialize();
    }

    public void btn_Save_OnClick(View v)
    {
        if(!mTextChanged)
        {
            return;
        }

        //todo check for data error
        EditText et = (EditText) findViewById(R.id.txt_StartCmd);
        setStartCommandString(et.getText().toString());

        et = (EditText) findViewById(R.id.txt_StopCmd);
        setStopCommandString(et.getText().toString());

        et = (EditText) findViewById(R.id.txt_Vid1Name);
        setVideoName(0, et.getText().toString());

        et = (EditText) findViewById(R.id.txt_Vid2Name);
        setVideoName(1,et.getText().toString());

        et = (EditText) findViewById(R.id.txt_Vid3Name);
        setVideoName(2,et.getText().toString());

        et = (EditText) findViewById(R.id.txt_IPAddr);
        setHostIpAddress(et.getText().toString());

        et = (EditText) findViewById(R.id.txt_Port);
        setHostPortNumber(Integer.parseInt(et.getText().toString()));

        savePersistentData();

        Toast.makeText(this, "Data Saved Successfully", Toast.LENGTH_SHORT).show();
        returnToUserInterface();
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

        (findViewById(R.id.btn_Save)).setEnabled(false);
    }

    private void fillFormData()
    {
        EditText et = (EditText) findViewById(R.id.txt_StartCmd);
        et.setText(getStartCommandString());

        et = (EditText) findViewById(R.id.txt_StopCmd);
        et.setText(getStopCommandString());

        et = (EditText) findViewById(R.id.txt_Vid1Name);
        et.setText(getVideoName(0));

        et = (EditText) findViewById(R.id.txt_Vid2Name);
        et.setText(getVideoName(1));

        et = (EditText) findViewById(R.id.txt_Vid3Name);
        et.setText(getVideoName(2));

        et = (EditText) findViewById(R.id.txt_IPAddr);
        et.setText(getHostIpAddress());

        et = (EditText) findViewById(R.id.txt_Port);
        et.setText(String.valueOf(getHostPortNumber()));
    }

    public native String getStartCommandString();
    public native String getStopCommandString();
    public native String getVideoName(int id);
    public native String getHostIpAddress();
    public native int getHostPortNumber();


    public native void setStartCommandString(String cmd);
    public native void setStopCommandString(String cmd);
    public native void setVideoName(int id, String name);
    public native void setHostIpAddress(String address);
    public native void setHostPortNumber(int port);

    public native void savePersistentData();

    static {
        System.loadLibrary("native-lib");
    }

    private boolean mTextChanged;

}
