//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include "Ensemble.h"
#include "DotGrid.h"
#include "Cursor.h"

class Sequencer: public UIComponent, public ClockListener
{
public:
    Sequencer();
    Sequencer(int x, int y, int width, int height);
    ~Sequencer();

// MARK: - Drawing & UIComponent API

public:
    void draw() override;
    
    void setPositionWithOrigin(const int x, const int y) override;
    
    void setPositionWithCentre(const int x, const int y) override;
    
    void setSizeFromCentre(const float width, const float height) override;
    
    void setSize(const float width, const float height) override;
    
    void setMargins(const int top, const int left, const int right, const int bottom) override;

    [[nodiscard]] const UIMargins<int>& getMargins() const noexcept override;

// MARK: - Clock control
    
public:
    /// @brief The callback that's executed when the sequencer's clock ticks.

    void tick() override;
    
    /// @brief Toggle the sequencer's clock.

    void toggleClock() noexcept;
    

public:
    /// @brief Return a textual description of the sequencer's contents at the cursor's current position.

    inline std::string_view getHoverDescription() noexcept
    {
        return hoverDescription;
    }

// MARK: - Sequencer cursor

public:
    /// @brief Move the sequencer's active cursor in the given direction.
    /// @param direction The direction in which the active cursor should be moved.

    void moveCursor(Direction direction) noexcept;

    /// @brief Move the sequencer's cursor to the grid position nearest to the given screen position.
    /// @param x The x-coordinate of the desired screen position.
    /// @param y The y-coordinate of the desired screen position.

    void moveCursorToScreenPosition(const int x, const int y) noexcept;

    /// @brief Set the octave value of the cursor's MIDI settings.
    /// @param octave The desired octave number in the range [0, 6].

    void setCursorOctave(const int octave) noexcept;

    /// @brief Set the channel value of the cursor's MIDI settings.
    /// @param channel The desired channel number in the range [1, 16].

    void setCursorChannel(const int channel) noexcept;

    /// @brief Set the duration value of the cursor's MIDI settings.
    /// @param duration The desired duration value in the range [1, 8].

    void setCursorDuration(const int duration) noexcept;

// MARK: - Sequence contents
    
public:
    /// @brief Place a new note at the sequencer cursor's current position.
    /// @param noteIndex A number in the range [0, 11] representing a note from the chromatic scale, beginning with C.
    /// @return A Boolean value to indicate whether the note was placed successfully or not.
    /// @throw An exception will be thrown in the case where the given position is out of range.

    bool placeNote(uint8_t noteIndex) noexcept(false);
    
    /// @brief Place a new portal node at the sequencer cursor's current position.
    /// @return A Boolean value to indicate whether the node was placed successfully or not.
    /// @throw An exception will be thrown in the case where the given position is out of range.
    
    bool placePortal() noexcept(false);
    
    /// @brief Place a new redirect node at the sequencer cursor's current position.
    /// @param type The desired type of redirect node to place.
    /// @return A Boolean value to indicate whether the node was placed successfully or not.
    /// @throw An exception will be thrown in the case where the given position is out of range.

    bool placeRedirect(Redirection type) noexcept(false);
    
    /// @brief Place a new playhead at the sequencer cursor's current position.
    /// @param direction The desired direction of the playhead node.

    void placePlayhead(Direction direction) noexcept;

    /// @brief Erase the contents of the sequencer at the sequencer cursor's current position.
    /// @throw An exception will be thrown in the case where the given position is out of range.

    void eraseFromCurrentPosition() noexcept(false);

// MARK: - Private functions

private:
    /// @brief Update the underlying data structures to reflect a change in the size of the sequencer grid.

    void gridDimensionsDidUpdate() noexcept(false);
    
    /// @brief Update the string that describes the contents of the sequencer at the cursor's current position.

    void updateHoverDescriptionString() noexcept;
    
    /// @brief Draw the subsequence at the cursor's current position if the user has requested to view an expanded subsequence.

    void drawSubsequenceIfRequested() noexcept;

private:
    Clock      clock;
    Cursor     cursor;
    DotGrid    grid;
    MIDIServer midiServer;
    
private:
    /// @brief A textual description of the sequence's contents at the cursor's current position.

    std::string hoverDescription;
    
    /// @brief Whether or not the user is viewing an expanded subsequence.

    bool viewingSubsequence = false;

private:
    using NodePtr = std::shared_ptr<SQNode>;
    std::vector<SQPlayhead> playheads;
    std::vector<SQPortal *> unpairedPortals;
    Table<NodePtr> table;
};

#endif
