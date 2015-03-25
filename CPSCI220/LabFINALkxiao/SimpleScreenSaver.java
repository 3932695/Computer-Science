import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class SimpleScreenSaver extends JFrame {
  public AnimationDemo() {
    // Create two MovingMessagePanel for displaying two moving messages
    this.setLayout(new GridLayout(2, 1));
    add(new MovingMessagePanel("Hello POPL Students!"));
    add(new MovingMessagePanel("It is almost over ;-)"));
  }

  /** Main method */
  public static void main(String[] args) {
    AnimationDemo frame = new SimpleScreenSaver();
    frame.setTitle("AnimationDemo");
    frame.setLocationRelativeTo(null); // Center the frame
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(280, 100);
    frame.setVisible(true);
  }

  // Inner class: Displaying a moving message
  static class MovingMessagePanel extends JPanel {

// FILL THIS IN

  }
}
