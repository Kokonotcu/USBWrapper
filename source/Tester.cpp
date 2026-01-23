#include "Tester.h"

namespace Songs
{
	Song Tetris({

        // === SECTION A ===

      // Bar 1: E (long) - B - C
      timestamp(0,  {76}), // E5
      timestamp(1,  {}),   // Sustain/Rest
      timestamp(2,  {71}), // B4
      timestamp(3,  {72}), // C5

      // Bar 2: D (long) - C - B
      timestamp(4,  {74}), // D5
      timestamp(5,  {}),
      timestamp(6,  {72}), // C5
      timestamp(7,  {71}), // B4

      // Bar 3: A (long) - A - C
      timestamp(8,  {69}), // A4
      timestamp(9,  {}),
      timestamp(10, {69}), // A4
      timestamp(11, {72}), // C5

      // Bar 4: E (long) - D - C
      timestamp(12, {76}), // E5
      timestamp(13, {}),
      timestamp(14, {74}), // D5
      timestamp(15, {72}), // C5

      // Bar 5: B (long) - C - D
      timestamp(16, {71}), // B4
      timestamp(17, {}),
      timestamp(18, {72}), // C5
      timestamp(19, {74}), // D5

      // Bar 6: E (long) - C (long)
      timestamp(20, {76}), // E5
      timestamp(21, {}),
      timestamp(22, {72}), // C5
      timestamp(23, {}),

      // Bar 7: A (long) - A (long)
      timestamp(24, {69}), // A4
      timestamp(25, {}),
      timestamp(26, {69}), // A4
      timestamp(27, {}),

      // Bar 8: Rest (Transition to B part)
      timestamp(28, {}),
      timestamp(29, {}),
      timestamp(30, {}),
      timestamp(31, {}),


      // === SECTION B ===

      // Bar 9: D (long) - F - A (high)
      timestamp(32, {74}), // D5
      timestamp(33, {}),
      timestamp(34, {77}), // F5
      timestamp(35, {81}), // A5

      // Bar 10: A (sustain) - G - F
      timestamp(36, {}),
      timestamp(37, {79}), // G5
      timestamp(38, {77}), // F5

      // Bar 11: E (long) - C - E
      timestamp(39, {76}), // E5
      timestamp(40, {}),
      timestamp(41, {72}), // C5
      timestamp(42, {76}), // E5

      // Bar 12: E (sustain) - D - C
      timestamp(43, {}),
      timestamp(44, {74}), // D5
      timestamp(45, {72}), // C5

      // Bar 13: B (long) - C - D
      timestamp(46, {71}), // B4
      timestamp(47, {}),
      timestamp(48, {72}), // C5
      timestamp(49, {74}), // D5

      // Bar 14: E (long) - C (long)
      timestamp(50, {76}), // E5
      timestamp(51, {}),
      timestamp(52, {72}), // C5
      timestamp(53, {}),

      // Bar 15: A (long) - A (long)
      timestamp(54, {69}), // A4
      timestamp(55, {}),
      timestamp(56, {69}), // A4
      timestamp(57, {}),

      // Bar 16: Rest / Loop buffer
      timestamp(58, {}),
      timestamp(59, {}),
      timestamp(60, {}),
      timestamp(61, {}),
		});
}

void Tester::Init()
{
	Songs::Tetris.SetResolution(resolution); // 2 ticks per second
	Songs::Tetris.Init();
	tracker = Time::RequestTracker(1/resolution);
	initialized = true;
}

void Tester::RunTests()
{
	if (!initialized)
		Init();

	std::vector<note> notes = Songs::Tetris.Advance().notes;

	if (activeNotes.size() == 0)
		activeNotes = notes;

	for (auto note : notes)
	{
		Synthesizer::ProcessNoteOn(note, 25);
	}

	if (tracker->CheckOnce())
	{
		for (auto note : activeNotes)
		{
			Synthesizer::ProcessNoteOff(note);
		}
		activeNotes = notes;
	}
	
}