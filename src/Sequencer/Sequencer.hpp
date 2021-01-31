//  Ensemble
//  Created by David Spry on 20/12/20.

#ifndef SEQUENCER_HPP
#define SEQUENCER_HPP

#include "Ensemble.h"
#include "DotGrid.h"
#include "Cursor.h"
#include "SequencerStateDescription.hpp"

class Sequencer: public UIComponent, public ClockListener
{
public:
    Sequencer();
    Sequencer(int x, int y, int width, int height);
    ~Sequencer();

// MARK: - Drawing & UIComponent API

public:
    /// @brief Draw the sequencer's contents in the current graphics context.

    void draw() override;
    
    /// @brief Set the position of the sequencer and its contents by the given origin point.
    /// @param x The x-coordinate of the desired origin point.
    /// @param y The y-coordinate of the desired origin point.

    void setPositionWithOrigin(const int x, const int y) override;
    
    /// @brief Set the position of the sequencer and its contents by the given centre point.
    /// @param x The x-coordinate of the desired centre point.
    /// @param y The y-coordinate of the desired centre point.

    void setPositionWithCentre(const int x, const int y) override;
    
    /// @brief Set the size of the sequencer and its contents while maintaining the current centre point.
    /// @param width The desired width in pixels.
    /// @param height The desired height in pixels.

    void setSizeFromCentre(const float width, const float height) override;
    
    /// @brief Set the size of the sequencer and its contents while maintaining the current origin point.
    /// @param width The desired width in pixels.
    /// @param height The desired height in pixels.

    void setSize(const float width, const float height) override;
    
    /// @brief Set the sequencer's margins.
    /// @param top The desired top margin in pixels.
    /// @param left The desired left margin in pixels.
    /// @param right The desired right margin in pixels.
    /// @param bottom The desired bottom margin in pixels.

    void setMargins(const int top, const int left, const int right, const int bottom) override;

    /// @brief Return the sequencer's margins.

    [[nodiscard]] const UIMargins<int>& getMargins() const noexcept override;

// MARK: - Clock control
    
public:
    /// @brief The callback that's executed when the sequencer's clock ticks.

    void tick() override;
    
    /// @brief Toggle the sequencer's clock.

    void toggleClock() noexcept;
    

public:
    /// @brief Return a textual description of the sequencer's contents at the cursor's current position.

    inline SequencerStateDescription & getSequencerStateDescription() noexcept
    {
        return stateDescription;
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
    
    /// @brief Select the previous available MIDI channel for the sequencer's cursor.
    
    void selectPreviousCursorChannel() noexcept;
    
    /// @brief Select the next available MIDI channel for the sequencer's cursor.
    
    void selectNextCursorChannel() noexcept;

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
    
    /// @brief Expand and view the subsequence at the sequencer cursor's current position.

    void expandSubsequence() noexcept;
    
// MARK: - Playhead selection
public:
    /// @brief Toggle the playhead selection mode.

    void toggleSelectPlayheadsMode() noexcept;
    
    /// @brief Enable or disable the selected playhead.

    void toggleSelectedPlayhead() noexcept;
    
    /// @brief Select the next playhead on the sequencer.
    
    inline void selectNextPlayhead() noexcept
    {
        selectPlayheadSuccessor(true);
    }
    
    /// @brief Select the previous available playhead on the sequencer.
    
    inline void selectPreviousPlayhead() noexcept
    {
        selectPlayheadSuccessor(false);
    }
    
private:
    /// @brief Select the successor playhead.
    /// @param next Whether the next playhead or the previous playhead should be selected.

    void selectPlayheadSuccessor(bool next) noexcept;
    
    /// @brief Erase the selected playhead.
    /// @note  The sequencer must be in playhead selection mode.
    
    void eraseSelectedPlayhead() noexcept;

// MARK: - Private functions

private:
    /// @brief Initialise the sequencer and its state description object.

    void initialise() noexcept;
    
    /// @brief Update the underlying data structures to reflect a change in the size of the sequencer grid.

    void gridDimensionsDidUpdate() noexcept(false);
    
    /// @brief Update the contents of the sequencer's state description object to reflect a change in the sequencer's cursor.

    void updateCursorStateDescription() noexcept;
    
    /// @brief Update the contents of the sequencer's state description object to reflect a change in the sequencer's MIDI components.
    
    void updateMIDIStateDescription() noexcept;
    
    /// @brief Draw the subsequence at the cursor's current position if the user has requested to view an expanded subsequence.

    void drawSubsequenceIfRequested() noexcept;

private:
    /// @brief The sequencer's clock interface, which wraps both an internal clock and an external clock.

    Clock clock;
    
    /// @brief The sequencer's cursor.

    Cursor cursor;
    
    /// @brief The sequencer's grid.

    DotGrid grid;
    
    /// @brief The sequencer's MIDI server, which manages the broadcast of MIDI notes.

    MIDIServer midiServer;

    /// @brief A collection of data from which a textual description of the sequencer's state can be derived.

    SequencerStateDescription stateDescription;

private:
    /// @brief Whether or not the user is viewing an expanded subsequence.

    bool isViewingSubsequence = false;
    
    /// @brief Whether or not the user is selecting a playhead node.

    bool isSelectingPlayheads = false;
    
    /// @brief The index of the currently selected playhead node.

    int selectedPlayheadIndex = 0;

private:
    std::vector<SQPlayhead> playheads;
    std::vector<SQPortal *> unpairedPortals;
    using NodePtr = std::shared_ptr<SQNode>;
    Table<NodePtr> table;
};

#endif
