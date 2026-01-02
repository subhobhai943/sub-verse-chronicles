package `in`.sub.unit.subverse

import android.content.Context
import android.graphics.Typeface
import android.view.Gravity
import android.view.View
import android.widget.Button
import android.widget.LinearLayout
import android.widget.TextView
import androidx.core.view.setPadding

class DialogueOverlay(context: Context) : LinearLayout(context) {

    private val speakerView = TextView(context)
    private val textView = TextView(context)
    private val choicesContainer = LinearLayout(context)

    var onAdvance: (() -> Unit)? = null
    var onChoose: ((Int) -> Unit)? = null

    init {
        orientation = VERTICAL
        setPadding(28)
        setBackgroundColor(0xCC0A0A0A.toInt())

        speakerView.setTextColor(0xFFF2F2F2.toInt())
        speakerView.textSize = 18f
        speakerView.typeface = Typeface.DEFAULT_BOLD

        textView.setTextColor(0xFFF2F2F2.toInt())
        textView.textSize = 16f

        choicesContainer.orientation = VERTICAL
        choicesContainer.visibility = View.GONE

        addView(speakerView, LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT))
        addView(textView, LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT))
        addView(choicesContainer, LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT))

        // tap anywhere on box to advance
        setOnClickListener { onAdvance?.invoke() }
        gravity = Gravity.BOTTOM
    }

    fun render(speaker: String, text: String, choices: List<String>) {
        speakerView.text = speaker
        textView.text = text

        choicesContainer.removeAllViews()
        if (choices.isEmpty()) {
            choicesContainer.visibility = View.GONE
        } else {
            choicesContainer.visibility = View.VISIBLE
            choices.forEachIndexed { idx, label ->
                val btn = Button(context)
                btn.text = label.trim()
                btn.setAllCaps(false)
                btn.setOnClickListener { onChoose?.invoke(idx) }
                choicesContainer.addView(btn, LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT))
            }
        }
    }
}
