package com.arc.prith.androidremotecontrol;

import android.content.Intent;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.Toast;

import java.util.ArrayDeque;
import java.util.Queue;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);

        initializeNativeComponents(getApplicationContext().getFilesDir() + "/" + getString(R.string.data_file_name));

        //hide admin credentials
        LinearLayout layout = (LinearLayout) findViewById(R.id.layout_AdminCredentials);
        layout.setVisibility(View.INVISIBLE);
        mCurrentlyPlaying = false;
    }

    public MainActivity()
    {
        mCurrentlyPlaying = false;
        mPlaylist = new ArrayDeque<>();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
    }

    private void stopVideoCommand(int vidId)
    {
        stopVideo(vidId);
        mCurrentlyPlaying = false;
    }

    private void playNextVideo()
    {
        if(mPlaylist.size() > 0) {
            final int vidId = mPlaylist.remove();
            final Handler handler = new Handler();
            handler.postDelayed(new Runnable() {
                @Override
                public void run() {
                    stopVideoCommand(vidId);
                    playNextVideo();
                }
            }, getVideoDelay(vidId));
            playVideo(vidId);
            mCurrentlyPlaying = true;
        }
    }

    public void btn_Vid1_OnClick(View v)
    {
        queueVideoCommand(Integer.parseInt(getText(R.string.vid1ID).toString()));
    }

    public void btn_Vid2_OnClick(View v)
    {
        queueVideoCommand(Integer.parseInt(getText(R.string.vid2ID).toString()));
    }

    public void btn_Vid3_OnClick(View v)
    {
        queueVideoCommand(Integer.parseInt(getText(R.string.vid3ID).toString()));
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

    private void queueVideoCommand(final int vidId)
    {
        mPlaylist.add(vidId);

        if(!mCurrentlyPlaying)
        {
            playNextVideo();
        }
    }

    Queue<Integer> mPlaylist;
    boolean mCurrentlyPlaying;

    public native void initializeNativeComponents(String dataFilePath);

    public native void playVideo(int vidId);

    public native void stopVideo(int vidId);

    public native int getVideoDelay(int vidId);

    static {
        // to support API 17 and lower, load all the native libraries in the order they are linked
        System.loadLibrary("PersistentDataManager");
        System.loadLibrary("Saveable");
        System.loadLibrary("NetworkController");
        System.loadLibrary("VideoPlayer");
        System.loadLibrary("native-lib");
    }
}
