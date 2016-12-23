package com.arc.prith.androidremotecontrol;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        initializeNativeComponents(getApplicationContext().getFilesDir() + "/" + getString(R.string.data_file_name));

        //hide admin credentials
        LinearLayout layout = (LinearLayout) findViewById(R.id.layout_AdminCredentials);
        layout.setVisibility(View.INVISIBLE);
    }

    @Override
    protected void onResume() {
        super.onResume();
    }

    public void btn_Vid1_OnClick(View v) {
        btnVid1_OnClick();
    }

    public void btn_Vid2_OnClick(View v) {
        btnVid2_OnClick();
    }

    public void btn_Vid3_OnClick(View v) {
        btnVid3_OnClick();
    }

    public void btn_RevealAdminCredentials_OnClick(View v)
    {
        LinearLayout layout = (LinearLayout) findViewById(R.id.layout_AdminCredentials);
        layout.setVisibility(View.VISIBLE);

        layout = (LinearLayout) findViewById(R.id.layout_UserInterface);
        layout.setVisibility(View.INVISIBLE);
    }

    public void btn_AdminLogIn_OnClick(View v)
    {
        EditText login = (EditText) findViewById(R.id.txt_loginID);
        EditText password = (EditText) findViewById(R.id.txt_Password);

        if (verifyCredentials(login.getText().toString(), password.getText().toString()))
        {
            Intent intent = new Intent(this, SettingsActivity.class);
            startActivity(intent);
            finish();
        }
        else
        {
            Toast.makeText(this, "Login Unsuccessfull", Toast.LENGTH_SHORT).show();
        }
    }

    public void btn_HideAdminCredentials_OnClick(View v)
    {
        LinearLayout layout = (LinearLayout) findViewById(R.id.layout_AdminCredentials);
        layout.setVisibility(View.INVISIBLE);

        layout = (LinearLayout) findViewById(R.id.layout_UserInterface);
        layout.setVisibility(View.VISIBLE);
    }

    public boolean verifyCredentials(String login, String password)
    {
        // currently we are only checking the values against the string resources
        String loginLowerCase = login.trim().toLowerCase();
        return loginLowerCase.equals(getString(R.string.admin).toLowerCase()) && password.equals(getString(R.string.adminPass));
    }



    public native void initializeNativeComponents(String dataFilePath);

    public native void btnVid1_OnClick();

    public native void btnVid2_OnClick();

    public native void btnVid3_OnClick();
    static {
        // to support API 17 and lower, load all the native libraries in the order they are linked
        System.loadLibrary("PersistentDataManager");
        System.loadLibrary("Saveable");
        System.loadLibrary("NetworkController");
        System.loadLibrary("VideoPlayer");
        System.loadLibrary("native-lib");
    }
}
