#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (800, 600);
    addAndMakeVisible(lowSlider);
    addAndMakeVisible(midSlider);
    addAndMakeVisible(highSlider);
    addAndMakeVisible(lowLabel);
    addAndMakeVisible(midLabel);
    addAndMakeVisible(highLabel);

    lowSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    midSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);
    highSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalDrag);

    lowLabel.setText("Low EQ", juce::NotificationType::dontSendNotification);
    midLabel.setText("Mid EQ", juce::NotificationType::dontSendNotification);
    highLabel.setText("High EQ", juce::NotificationType::dontSendNotification);

    lowLabel.setJustificationType(juce::Justification::centred);
    midLabel.setJustificationType(juce::Justification::centred);
    highLabel.setJustificationType(juce::Justification::centred);


    // Some platforms require permissions to open input channels so request that here
    if (juce::RuntimePermissions::isRequired (juce::RuntimePermissions::recordAudio)
        && ! juce::RuntimePermissions::isGranted (juce::RuntimePermissions::recordAudio))
    {
        juce::RuntimePermissions::request (juce::RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // This function will be called when the audio device is started, or when
    // its settings (i.e. sample rate, block size, etc) are changed.

    // You can use this function to initialise any resources you might need,
    // but be careful - it will be called on the audio thread, not the GUI thread.

    // For more details, see the help for AudioProcessor::prepareToPlay()
}

void MainComponent::getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill)
{
    // Your audio-processing code goes here!

    // For more details, see the help for AudioProcessor::getNextAudioBlock()

    // Right now we are not producing any data, in which case we need to clear the buffer
    // (to prevent the output of random noise)
    bufferToFill.clearActiveBufferRegion();
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!

}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    // set up the slider area

    auto area = getLocalBounds();
    auto sliderArea = area.removeFromBottom(200);

    // create the slider flex box
    juce::FlexBox sliderBox;
    
    sliderBox.flexDirection = juce::FlexBox::Direction::row;
    sliderBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    sliderBox.alignContent = juce::FlexBox::AlignContent::center;
    
    sliderBox.items.add(juce::FlexItem(lowSlider).withFlex(1.0f));
    sliderBox.items.add(juce::FlexItem(midSlider).withFlex(1.0f));
    sliderBox.items.add(juce::FlexItem(highSlider).withFlex(1.0f));

    sliderBox.performLayout(sliderArea);

    // create the text labels

    auto textArea = area.removeFromBottom(50);

    juce::FlexBox textBox;
    textBox.flexDirection = juce::FlexBox::Direction::row;
    textBox.justifyContent = juce::FlexBox::JustifyContent::spaceAround;
    textBox.alignContent = juce::FlexBox::AlignContent::center;

    textBox.items.add(juce::FlexItem(lowLabel).withFlex(1.0f));
    textBox.items.add(juce::FlexItem(midLabel).withFlex(1.0f));
    textBox.items.add(juce::FlexItem(highLabel).withFlex(1.0f));

    textBox.performLayout(textArea);


}
