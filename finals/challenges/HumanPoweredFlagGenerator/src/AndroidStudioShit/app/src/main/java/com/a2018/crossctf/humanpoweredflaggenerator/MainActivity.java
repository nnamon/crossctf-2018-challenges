package com.a2018.crossctf.humanpoweredflaggenerator;

import android.content.res.Resources;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    private Status status;
    private TextView flagDisplay;
    private TextView percent;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        status = new Status();

        flagDisplay = findViewById(R.id.flagTextView);
        percent = findViewById(R.id.percentTextView);

        findViewById(R.id.speedupButton).setOnClickListener(view -> status.speedUp());
        findViewById(R.id.crankButton).setOnClickListener(view -> crank());
    }

    private void crank() {
        status.crank(3.8);

        Resources res = getResources();
        flagDisplay.setText(res.getString(R.string.flag, status.flag()));
        percent.setText(res.getString(R.string.percent, status.level(), status.percent()));
    }
}

