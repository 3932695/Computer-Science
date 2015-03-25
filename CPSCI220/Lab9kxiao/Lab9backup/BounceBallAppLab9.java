import java.awt.*;
import javax.swing.*;

public class BounceBallAppLab9 extends JApplet {
  public BounceBallAppLab9() {
    add(new BallControlLab9());
  }

  public static void main(String[] args) {
    BounceBallAppLab9 applet = new BounceBallAppLab9();
    JFrame frame = new JFrame();
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setTitle("BounceBallAppLab9");
    frame.add(applet, BorderLayout.CENTER);
    frame.setSize(400, 320);
    frame.setVisible(true);
  }
}

