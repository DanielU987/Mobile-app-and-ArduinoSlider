package com.droiduino.bluetoothconn;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class EntryActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_entry);
        final Button startButton = findViewById(R.id.button_Start);
        startButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Move to adapter list
                Intent intent = new Intent(EntryActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });
        final Button InstructionButton = findViewById(R.id.button_instruction);
        InstructionButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Move to adapter list
                Intent intent = new Intent(EntryActivity.this, activity_instruction.class);
                startActivity(intent);
            }
        });
        final Button AboutButton = findViewById(R.id.button_About);
        AboutButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Move to adapter list
                Intent intent = new Intent(EntryActivity.this, activity_About.class);
                startActivity(intent);
            }
        });
        final Button ExitButton = findViewById(R.id.button_exit);
        ExitButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                // Move to adapter list
                finishAffinity();
            }
        });
    }
}