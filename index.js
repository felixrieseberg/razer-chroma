const native = require('bindings')('Chroma');

/**
 * Ensures that a color object is sound.
 *
 * @param {Object} color
 * @returns {color}
 *
 * @typedef color
 * @param {number} red
 * @param {number} green
 * @param {number} blue
 */
function checkColor(color) {
  color = color || {}

  if (color.red > 255 || color.red < 0) {
    throw new Error(`Color red needs to be between 0 and 255! It is: ${color.red}`)
  }

  if (color.blue > 255 || color.blue < 0) {
    throw new Error('Color blue needs to be between 0 and 255!')
  }

  if (color.green > 255 || color.green < 0) {
    throw new Error('Color green needs to be between 0 and 255!')
  }

  return color
}

module.exports = {
  /**
   * Initializes the Razer Chroma SDK.
   *
   * @return {boolean} success - Whether or not the SDK was initialized.
   * False means usually that there's no Chroma device.
   */
  initialize() {
    return native.initialize()
  },

  /**
   * Terminates the Razer Chroma SDK.
   *
   * @return {boolean} success - Whether or not the SDK was initialized.
   * False means usually that it wasn't initialized.
   */
  terminate() {
    return native.terminate()
  },

  Keyboard: {
    /**
     * Show a "wave" effect on the keyboard
     *
     * @param {string} direction - Either 'leftToRight' or 'rightToLeft'
     *
     * @returns {void}
     */
    setWave(direction) {
      return native.Keyboard.setWave(direction || 'leftToRight')
    },

    /**
     * Sets the whole keyboard to a given color.
     *
     * @param {color} color
     *
     * @typedef color
     * @param {number} red
     * @param {number} green
     * @param {number} blue
     *
     * @returns {void}
     */
    setStatic(color) {
      color = checkColor(color)

      return native.Keyboard.setStatic(color)
    },

    /**
     * Set the keyboard to a custom array, allowing you to specify the
     * color for each key. The array should contain six arrays (for each row),
     * with each array containing 22 keys (for each column).
     *
     * @param {Array<Array<color>>} customArray
     *
     * @typedef color
     * @param {number} red
     * @param {number} green
     * @param {number} blue
     *
     * @returns {void}
     */
    setCustom(customArray) {
      if (!customArray) {
        throw new Error('setCustom must be called with an array as parameter.')
      }

      return native.Keyboard.setCustom(customArray)
    },

    /**
     * Set the keyboard to a breathing effect, using two given colors.
     *
     * @param {color} colorOne - A color object
     * @param {color} colorTwo - A color object
     * @returns {void}
     */
    setBreathing(colorOne, colorTwo) {
      colorOne = checkColor(colorOne)
      colorTwo = checkColor(colorTwo)

      return native.Keyboard.setBreathing(colorOne, colorTwo)
    },

    /**
     * Set the keyboard to a random breathing effect.
     *
     * @returns {void}
     */
    setBreathingRandom(colorOne, colorTwo) {
      return native.Keyboard.setBreathingRandom()
    },

    /**
     * Set the keyboard to a spectrum cycling effect.
     *
     * @returns {void}
     */
    setSpectrumCycling() {
      return native.Keyboard.setSpectrumCycling()
    },

    /**
     * Set the keyboard to a starlight effect, using random colors.
     *
     * @param {color} colorOne - A color object
     * @param {color} colorTwo - A color object
     * @returns {void}
     */
    setStarlight(colorOne, colorTwo) {
      colorOne = checkColor(colorOne)
      colorTwo = checkColor(colorTwo)
      return native.Keyboard.setStarlight(colorOne, colorTwo)
    },

    /**
     * Sets the whole keyboard to a reactive effect.
     *
     * @param {color} color
     *
     * @typedef color
     * @param {number} red
     * @param {number} green
     * @param {number} blue
     *
     * @returns {void}
     */
    setReactive(color) {
      color = checkColor(color)

      return native.Keyboard.setReactive(color)
    },
  }
};
