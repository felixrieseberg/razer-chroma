let exports

function boot () {
  if (process && process.versions && process.versions.electron) {
    // We're in electron-land, let's see if electron-remote is available
    try {
      const { requireTaskPool } = require('electron-remote')
      exports = requireTaskPool(require.resolve('./index'))
      return
    } catch (error) {
      console.warn(`Running razer-chroma within Electron. In this case, we heavily recommend running it with electron-remote`)
      console.warn(`To do so, simply run "npm install --save electron-remote`)
    }
  }

  exports = require('./index')
}

boot()
module.exports = exports
