import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.Timer;

public class SimpleScreenSaver2 extends JFrame {
    public SimpleScreenSaver2() {
	// Create two MovingMessagePanel for displaying two moving messages
	this.setLayout(new GridLayout(2, 1));
	add(new MovingMessagePanel("Hello POPL Students!"));
	add(new MovingMessagePanel("It is almost over ;-)"));
    }

    /** Main method */
    public static void main(String[] args) {
	SimpleScreenSaver2 frame = new SimpleScreenSaver2();
	frame.setTitle("SimpleScreenSaver2");
	frame.setLocationRelativeTo(null); // Center the frame
	frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	frame.setSize(280, 100);
	frame.setVisible(true);
    }

    // Inner class: Displaying a moving message
    static class MovingMessagePanel extends JPanel {
	private int delay = 10;

	// Create a timer with delay 1000 ms
	private Timer timer = new Timer(delay, new TimerListener());

	private int x = 0; private int y = 0; // Current text position
	private String text; // text
	private int radius = 1;
	private int dx = 2; // Increment on ball's x-coordinate
	private int dy = 2; // Increment on ball's y-coordinate

	public MovingMessagePanel(String string) {
	    timer.start();		   
	    text = string;
	}

	private class TimerListener implements ActionListener {
	    @Override /** Handle the action event */
		public void actionPerformed(ActionEvent e) {
		repaint();
	    }
	}

	@Override
	    protected void paintComponent(Graphics g) {
	    super.paintComponent(g);

	    g.setColor(Color.red);

	    // Check boundaries
	    if (x < 0 || x > getWidth()) 
		dx *= -1;
	    if (y < 0 || y > getHeight()) 
		dy *= -1;

	    // Adjust ball position
	    x += dx;
	    y += dy;
	    g.fillOval(x - radius, y - radius, radius * 2, radius * 2);
	    add(new JTextArea(text, x, y));
	}

	public void suspend() {
	    timer.stop(); // Suspend timer
	}

	public void resume() {
	    timer.start(); // Resume timer
	}

	public void setDelay(int delay) {
	    this.delay = delay;
	    timer.setDelay(delay);
	}
    }
}
