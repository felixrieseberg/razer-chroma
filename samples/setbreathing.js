const chroma = require('../index')
const utils = require('./utils')

const initialize = chroma.initialize()

if (initialize) {
  console.log(chroma)
  chroma.Keyboard.setBreathing({red: 255, green: 0, blue: 0}, {red: 255, green: 0, blue: 0});
  utils.pressKeyToExit(chroma)
} else {
  console.log(`Failed to initialize!`)
}
